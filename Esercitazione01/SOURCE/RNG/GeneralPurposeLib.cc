#include "GeneralPurposeLib.h"

#include <iostream>
#include <math.h>
#include <fstream>
#include <functional>
#include "random.h"

using namespace std;

// Inizializza generatore da seed.in
void Initialize(Random* rnd){
	int seed[4];
	int p1, p2;
	
	ifstream Primes("RNG/Primes");
	if (Primes.is_open())
		Primes >> p1 >> p2;
		else
			cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();
	
	ifstream input("RNG/seed.in");
	string property;
	if (input.is_open()){
		while(!input.eof()){	
			input >> property;
			if (property == "RANDOMSEED"){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				rnd->SetRandom(seed, p1, p2);
			}
		}
		
		input.close();
	}
		else
			cerr << "PROBLEM: Unable to open seed.in" << endl;

}
// Compie media aritmetica su numeri campionati da distr uniforme
double MediaRandom (Random* r, int throws){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= r->Rannyu();
	sum = sum/throws;
	
	return sum;
	
}
// Calcola la media aritmetica su throws campionamenti della varianza per una
// distr uniforme
double MediaVarRandom (Random* r, int throws, double mean){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= pow((r->Rannyu() - mean), 2);
	sum = sum/throws;
	
	return sum;
	
}
// Media aritmentica su throws singole stime di pi con metodo di Buffon
double MediaBuffon(Random* r, int throws, double d, int nthr){
	double sum = 0;
	for (int i = 0; i < throws; i++){
		int nhit = 0;
		for (int j = 0; j < nthr; j++){
			double y = sin(8*Theta(r));
			double cm = d * r->Rannyu();	//posizione del centro dell'ago
			if (cm + y > d or cm - y < 0)	//se la proiezione sull'asse y dell'ago è fuori dall'intervallo (0,d)
				nhit++;						//allora interseca
		}
		sum += 2 * nthr / (nhit * d);
	}
	sum = sum/throws;
	
	return sum;
}
// Media aritmetica di elementi di vettore
double MediaVector (double* vec, int n){
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += vec[i];
	sum = sum/n;
	
	return sum;

}
// Svuota
void EmptyVectorInt(int* vec, int n){
	for (int i = 0; i < n; i++)
		vec[i] = 0.;
}
// Formula per incertezza statistica
double Error (double a, double b, int n){
	if (n == 0)
		return 0;
		else
			return sqrt( (a - b*b) / n );
}
// Chi2 per istogramma (int* counts)
double Chi2 (int* counts, double mean, int intervals){
	double chi2 = 0;
	for (int i = 0; i < intervals; i++)
		chi2 += pow((counts[i] - mean), 2)/mean;
	
	return chi2;
		
}
// Riempie istogramma (il vettore counts) con throws lanci
void Fill(int* counts, Random* r, int throws, int intervals){
	double step = 1./(double)intervals;
	for (int i = 0; i < throws; i++)
	{
		double x = r->Rannyu();
  		int bin = static_cast<int>(x/step);
  		counts[bin]++;
  	}

}
// Campionare distr uniforme
double Uniform(Random* r, double* par){
	return r->Rannyu();
}
// Campionare distr esponenziale (con metodo ICF)
double ExpICF(Random* r, double* par){
	return -log(1.-r->Rannyu())/par[0];
}
// Campionare Lorentziana (metodo ICF)
double LorentzICF(Random* r, double*par){
	//par[0] è gamma, par[1] è mu
	return par[0]*tan(M_PI*(r->Rannyu() - .5)) + par[1];
}
// Media su throws lanci di variabile campionata da f
double Distributions(Random *r, int throws, std::function<double(Random*, double*)> f, double* par){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= f(r, par);
	sum = sum/throws;
	
	return sum;
	return 0;
}
// Campiona angolo fra 0 e M_PI/4
double Theta(Random* r){
	double x, y;	
	double theta = -1;
		while (theta == -1)
		{
			x = r->Rannyu();
			y = r->Rannyu();
			if (y == 0)
				theta = 0.;
			if (sqrt(x*x + y*y) < 1)
				theta = atan(x/y);
		}
	return theta;
}








 
