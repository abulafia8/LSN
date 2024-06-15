#include "Lib.h"

#include <iostream>
#include <math.h>
#include <fstream>
#include <functional>
#include <armadillo>
#include <numeric>
#include <cmath>

#include "Walker.h"

using namespace std;

//Media su elementi di std vector
double MediaStdVector (vector<double> vector){
    double sum = 0;
    for (int i = 0; i < (int)vector.size(); i++)
        sum += vector[i];
    return sum / vector.size();
}
//Deviazione standard: divide in blocchi e calcola errore
double StdDev(vector<double> v, int bl_size){
    vector <double> vec;
    vector <double> temp;
    for (int i = 0; i < (int)v.size() / bl_size; i++){
        for (int j = i*bl_size; j < (i+1)*bl_size; j++){
            temp.push_back(v[j]);
        }
        vec.push_back(MediaStdVector(temp));
        temp.clear();
    }

    vector<double> squares(vec.size());
    transform(vec.begin(), vec.end(), squares.begin(), [](double x) { return x * x; });
    return  Error(MediaStdVector(squares), MediaStdVector(vec), (int)vec.size());
}
//Funzione ancillare
double Gaussian(double x, double mu, double sigma){
    double x2 = (x - mu)*(x - mu);
    return exp(-0.5 * x2 / (sigma * sigma));
}
//Funzione campionabile da questo Metropolis
double PsiTrial (vec x, vec pars){
    return Gaussian(x(0), pars(0), pars(1)) + Gaussian(x(0), -pars(0), pars(1));
}
//Funzione ancillare
double DoubleWell (double x){
    return pow(x, 4) - 2.5 * pow(x, 2);
}
//Funzione ancillare: Espressione analitica hamiltoniana (come figura in integrale)
double Hamiltonian (vec x, vec pars, function<double(vec, vec)> f){
    double d = .01; 
    return -.5 * ((f(x - d, pars) + f(x + d, pars) - 2*f(x, pars))/(d*d)) / f(x, pars) + DoubleWell(x(0));
}
//Funzione ancillare: Valore dell'hamiltoniana in un blocco, campiona PsiTrial
double MediaHamiltonian (Walker* walker, int Length){
    double sum = 0;
    for (int i = 0; i < Length; i ++){
        walker->Move();
        sum += Hamiltonian(walker->GetX(), walker->GetPars(), walker->GetFunction());
    }
    return sum / double(Length);   
}
//Funzione ancillare: Media a blocchi su risultati di MediaHamiltonian, per avere incertezza
vector<double> H(vec x){
    Random rnd; 
    vec start = {.0};   
    Walker walker = Walker(&rnd, start, PsiTrial, x, 0);  
    vector<double> stoch;
	vector<double> stoch2;
    int L = 2000;
    int N = 20;

    for (int i = 0; i < .5*L; i++) 
        walker.Move();
    for (int i = 0; i < N; i++){
        double h = MediaHamiltonian(&walker, L);
		stoch.push_back(h); 
		stoch2.push_back(stoch[i]*stoch[i]);
	}

    double H = MediaStdVector(stoch);
    double err = sqrt(fabs(MediaStdVector(stoch2) - H*H) / (stoch.size()));
    vector<double> res; res.push_back(H); res.push_back(err);

    return res;
}

//Funzione campionabile da questo Metropolis: argomento diviso per 1/2 perché in Move() viene elevato alla 2 
double Boltzmann (vec x, vec y){
    vector<double> hamiltonian = H(x);
    double E = hamiltonian[0];

    return exp (-.5*y(0)*E);   
}


























