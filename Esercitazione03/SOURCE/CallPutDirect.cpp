#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "LibPricing.h"

#define M 1000000
#define N_BLOCKS 100

using namespace std;

int main (int argc, char *argv[]){
	int L = M/N_BLOCKS;
	double stoch[N_BLOCKS];
	double stoch2[N_BLOCKS];
	double prog_avg[N_BLOCKS];
	double prog_avg2[N_BLOCKS];
	double err_prog[N_BLOCKS];
	ofstream CallFile("../OUTPUT/CallPriceDirect.dat");
	ofstream PutFile("../OUTPUT/PutPriceDirect.dat");
	
	Random rnd;
	Initialize(&rnd);
	
	//PREZZO CALL TRAMITE CAMPIONAMENTO
	for (int i = 0; i < N_BLOCKS; i++){
		stoch[i] = MediaProfitDir('c', L, &rnd);
		stoch2[i] = stoch[i]*stoch[i];
		
		prog_avg[i] = MediaVector(stoch, i+1);
		prog_avg2[i] = MediaVector(stoch2, i+1);
		err_prog[i] = Error(prog_avg2[i], prog_avg[i], i);
		
		CallFile << prog_avg[i] << "\t" << err_prog[i] << endl;
	}
	
	//PREZZO PUT TRAMITE CAMPIONAMENTO
	for (int i = 0; i < N_BLOCKS; i++){
		stoch[i] = MediaProfitDir('p', L, &rnd);
		stoch2[i] = stoch[i]*stoch[i];
		
		prog_avg[i] = MediaVector(stoch, i+1);
		prog_avg2[i] = MediaVector(stoch2, i+1);
		err_prog[i] = Error(prog_avg2[i], prog_avg[i], i);
		
		PutFile << prog_avg[i] << "\t" << err_prog[i] << endl;
	}
	
	CallFile.close(); 
	PutFile.close();
	rnd.SaveSeed();
 	return 0;
}

