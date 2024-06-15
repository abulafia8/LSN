//AD OGNI PASSO i:

	//10mila (M) camminatori si muovono
	//si ottiene un valore della radice quadrata della distanza media quadrata per ogni blocco (tramite MediaDist(walkers, #Blocco))
	//si hanno così NBlocchi variabili stocastiche
	//su di esse si fa media e scarto quadratico medio
//ripetuto STEPS volte

#include <iostream>
#include <math.h>
#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "Walker.h"
#include "WalkLib.h"

#define M 10000
#define STEPS 10000
#define N_BLOCKS 100
#define A 1

using namespace std;

int main (int argc, char *argv[]){
	//PREP
	Random rnd;
	Initialize(&rnd);

	int BLOCK_SIZE = M/N_BLOCKS;
    double stoch[N_BLOCKS];
	double stoch2[N_BLOCKS];
	double prog_avg[STEPS];
	double prog_avg2[STEPS];
	
	ofstream OutFile("../OUTPUT/DistanzeCRW.dat");
	Walker* Party = new Walker[M];
	for (int i = 0; i < M; i++)
		Party[i] = Walker(A, &rnd);


	//CAMMINI
	for (int i = 0; i < STEPS; i++){
		for (int j = 0; j < M; j++)
			Party[j].TakeContStep();
			
		for (int j = 0; j < N_BLOCKS; j++){											
			stoch[j] = MediaDistBlock(Party, j, BLOCK_SIZE);
			stoch2[j] = stoch[j] * stoch[j];
		}
		
		prog_avg[i] = MediaVector(stoch, N_BLOCKS); 
		prog_avg2[i] = MediaVector(stoch2, N_BLOCKS);
		
		OutFile << prog_avg[i] << "\t" << Error(prog_avg2[i], prog_avg[i], N_BLOCKS - 1) << endl;	
	}

	//WRAP UP
	OutFile.close(); 
    rnd.SaveSeed();
 	return 0;
}