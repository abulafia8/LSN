#include <iostream>
#include <math.h>
#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#define N 100

using namespace std;

int main (int argc, char *argv[])
{
	Random rnd;
	int M = 100000;
	int L = M/N;
	double stoch[N];
	double stoch2[N];
	double prog_avg[N];
	double prog_avg2[N];
	double err_prog[N];
	ofstream OutFile("../OUTPUT/MedieRNG.dat");
	
	Initialize(&rnd);
	for (int i = 0; i < N; i++){
		stoch[i] = MediaRandom(&rnd, L);
		stoch2[i] = stoch[i]*stoch[i];
		
		prog_avg[i] = MediaVector(stoch, i+1);
		prog_avg2[i] = MediaVector(stoch2, i+1);
		err_prog[i] = Error(prog_avg2[i], prog_avg[i], i);
		
		OutFile << prog_avg[i] << "\t" << err_prog[i] << endl;
	}
		
	OutFile.close();   
	rnd.SaveSeed();
 	return 0;
}
