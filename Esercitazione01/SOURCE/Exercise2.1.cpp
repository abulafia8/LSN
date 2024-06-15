#include <iostream>
#include <math.h>
#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#define N 10000

#define L 1
#define MU 0 
#define G 1

using namespace std;

int main (int argc, char *argv[]){
	Random rnd;
	ofstream OutFile("../OUTPUT/Histograms.dat");
	double meanU, meanE, meanC;
	double parU[] = {0.};
	double parE[] = {L};
	double parC[] = {G, MU};
	int n[] = {1, 2, 10, 100};
	int length = (int)sizeof(n) / sizeof(int);
	Initialize(&rnd);
    // Ciclo su medie calcolate per 1, 2, 10, 100 campioni
	int k = 0;
	while(k < length){
		ofstream OutFile("../OUTPUT/Histograms" + to_string(n[k]) + ".dat");	
		for (int i = 0; i < N; i++){
			meanU = Distributions(&rnd, n[k], Uniform, parU);
			meanE = Distributions(&rnd, n[k], ExpICF, parE);
			meanC = Distributions(&rnd, n[k], LorentzICF, parC);
			OutFile << meanU << "\t\t" << meanE << "\t\t" << meanC << endl;
		}
		OutFile.close();
		k++;
	}

	rnd.SaveSeed();
 	return 0;
}
