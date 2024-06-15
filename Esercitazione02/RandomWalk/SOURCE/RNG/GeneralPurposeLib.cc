#include "GeneralPurposeLib.h"

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include "random.h"

using namespace std;

void Initialize(Random* rnd, int restart){
	int seed[4];
	int p1, p2;
	
	ifstream Primes("RNG/Primes");
	if (Primes.is_open())
		Primes >> p1 >> p2;
		else
			cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();
	
	string filename;
	if (restart == 0)
		filename = "RNG/seed.in";
	if (restart == 1)
		filename = "RNG/seed.out";

	ifstream input(filename);
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
		cerr << "PROBLEM: Unable to open " + filename << endl;
}


double MediaRandom (Random* r, int throws){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= r->Rannyu();
	sum = sum/throws;
	
	return sum;	
}

double MediaVarRandom (Random* r, int throws, double mean){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= pow((r->Rannyu() - mean), 2);
	sum = sum/throws;
	
	return sum;
}
 
double MediaVector (double* vec, int n){
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += vec[i];
	sum = sum/n;
	
	return sum;
}

double MediaStdVec(vector<double> vec){
	double sum = 0;
	for (int i = 0; i < (int)vec.size(); i++)
		sum += vec[i];
	sum = sum/((int)vec.size());
	
	return sum;
}

void EmptyVectorInt(int* vec, int n){
	for (int i = 0; i < n; i++)
		vec[i] = 0.;
}


double Error (double a, double b, int n){
	if (n == 0)
		return 0;
	else
		return sqrt( (a - b*b) / n );
}

double Chi2 (int* counts, double mean, int intervals){
	double chi2 = 0;
	for (int i = 0; i < intervals; i++)
		chi2 += pow((counts[i] - mean), 2)/mean;
	
	return chi2;	
}

void Fill(int* counts, Random* r, int throws, int intervals){
	double step = 1./intervals;
	for (int i = 0; i < throws; i++){
		double x = r->Rannyu();
  		int bin = static_cast<int>(x/step);
  		counts[bin]++;
  	}
}

double ExpICF(Random* r, double lambda){
	return -log(1.-r->Rannyu())/lambda;
}

double LorentzICF(Random* r, double gamma, double mu){
	return gamma*tan(M_PI*(r->Rannyu() - .5)) + mu;
}

double MediaRandomExp (Random* r, int throws, double lambda){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= ExpICF(r, lambda);
	sum = sum/throws;
	
	return sum;
	
}

double MediaRandomCauchy (Random* r, int throws, double gamma, double mu){
	double sum = 0;
	for (int i = 0; i < throws; i++)
		sum+= LorentzICF(r, gamma, mu);
	sum = sum/throws;
	
	return sum;
	
}


	




 
