#include "GeneralPurposeLib.h"

#include <iostream>
#include <math.h>
#include <fstream>
#include <functional>
#include "random.h"
#include "../Walker.h"

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
	else if (restart == 1)
		filename = "RNG/seed.out";
	else
		cerr << "Insert either 0 for first time, 1 to use seed.out" << endl;
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

double MediaVector (double* vec, int n){
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += vec[i];
	sum = sum/n;
	
	return sum;

}

double Error (double a, double b, int n){
	if (n == 0)
		return 0;
		else
			return sqrt( fabs(a - b*b) / n );
}


