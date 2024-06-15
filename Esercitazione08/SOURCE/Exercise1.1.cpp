#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "Walker.h"
#include "Lib.h"

#define M 100000
#define N 100 

using namespace std;

int main (int argc, char *argv[]){
    Random rnd;
    double stoch[N];
	double stoch2[N];
	double prog_avg[N];
	double prog_avg2[N];
	double err_prog[N];

	int L = M/N; 
    ofstream OutFile("../OUTPUT/Hamiltonian.dat");
	ifstream Parameters("../INPUT/InitialParameters.dat");
	double mu;	double sigma;
	double temp;
	Parameters >> mu >> temp; Parameters >> sigma;
	
	vec pars = {mu, sigma};
	vec start = {.0};
    Walker walker = Walker(&rnd, start, PsiTrial, pars);

    //Equilibrazione
    for (int i = 0; i < .5*L; i++) 
        walker.Move();
        
    for (int i = 0; i < N; i++){
		stoch[i] = MediaHamiltonian(&walker, L);
		stoch2[i] = stoch[i]*stoch[i];
		
		prog_avg[i] = MediaVector(stoch, i+1);
		prog_avg2[i] = MediaVector(stoch2, i+1);
		err_prog[i] = Error(prog_avg2[i], prog_avg[i], i);
		
		OutFile << prog_avg[i] << setw(18) << err_prog[i] << setw(18) <<  walker.GetAcceptance() << endl;
	}
	
	//Salva posizioni campionate per istogramma
	ofstream Positions("../OUTPUT/Positions.dat");
	vector<vec> path = walker.GetPath();
	for (int i = .5*L; i < M + .5*L; i++){
		Positions << path[i](0) << endl;
	}
	
	OutFile.close();
	Parameters.close();
	Positions.close();
    rnd.SaveSeed();
 	return 0;
}