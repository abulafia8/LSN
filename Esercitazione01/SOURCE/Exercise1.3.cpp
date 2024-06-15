#include <iostream>
#include <math.h>
#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#define M 100	// intervals (bins)
#define N 100000 //throws

using namespace std;

int main (int argc, char *argv[]){
	
	Random rnd;
	int bins[M];
	EmptyVectorInt(bins, M);
	ofstream OutFile("../OUTPUT/Chi2.dat");
	
	// Produce n stime per la varibile Chi2 
	int n = 10000;
	Initialize(&rnd);
	for (int i = 0; i < n; i++){
		Fill(bins, &rnd, N, M);	//genera N numeri random, li binna in M intervalli
		double chi2 = Chi2(bins, N/M, M);
		EmptyVectorInt(bins, M);
		OutFile << chi2 << endl;
	}
		
	OutFile.close();   
	rnd.SaveSeed();
 	return 0;
}

