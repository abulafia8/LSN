#include <fstream>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "LibPricing.h"
#include "WalkerSpot.h"

#define M 100000
#define N_BLOCKS 100
#define STEPS 100

using namespace std;

int main (int argc, char *argv[]){
    //PREP
    int BLOCK_SIZE = M/N_BLOCKS;

	double stochCall[N_BLOCKS];                     double stochPut[N_BLOCKS];
	double stochCall2[N_BLOCKS];                    double stochPut2[N_BLOCKS];
	double prog_avgCall[N_BLOCKS];                  double prog_avgPut[N_BLOCKS];
	double prog_avgCall2[N_BLOCKS];                 double prog_avgPut2[N_BLOCKS];
	double err_progCall[N_BLOCKS];                  double err_progPut[N_BLOCKS];
	ofstream CallFile("../OUTPUT/CallPriceWalk.dat");
	ofstream PutFile("../OUTPUT/PutPriceWalk.dat");

    Random rnd;
	Initialize(&rnd);

    double timeStep = 1./STEPS;
	WalkerSpot* Party = new WalkerSpot[M];
	for (int i = 0; i < M; i++)
		Party[i] = WalkerSpot(timeStep, &rnd);

    //BODY
    for (int i = 0; i < STEPS; i++)
        for (int j = 0; j < M; j++)
			Party[j].TakeStepSpot();
    
    for (int i = 0; i < N_BLOCKS; i++){
            //double FinalSpot = MediaDistSpot(Party, i, BLOCK_SIZE); //andrebbero invertiti? prima profit e poi ci si fa la media
            //double Price = Profit(FinalSpot, R, K, T, 'c');	
            //come mai invece non è meglio calcolando profitto con sqrt di media degli spot al quadrato?  
        double PriceCall = MediaProfitWalk(Party, i, BLOCK_SIZE, 'c'); 
        double PricePut = MediaProfitWalk(Party, i, BLOCK_SIZE, 'p'); 

		stochCall[i] = PriceCall;                                           stochPut[i] = PricePut;
		stochCall2[i] = stochCall[i] * stochCall[i];                        stochPut2[i] =  stochPut[i] * stochPut[i];  

        prog_avgCall[i] = MediaVector(stochCall, i+1);                      prog_avgPut[i] = MediaVector(stochPut, i+1); 
		prog_avgCall2[i] = MediaVector(stochCall2, i+1);                    prog_avgPut2[i] = MediaVector(stochPut2, i+1);
		err_progCall[i] = Error(prog_avgCall2[i], prog_avgCall[i], i);      err_progPut[i] = Error(prog_avgPut2[i], prog_avgPut[i], i);

		CallFile << prog_avgCall[i] << "\t" << err_progCall[i] << endl;
        PutFile << prog_avgPut[i] << "\t" << err_progPut[i] << endl;
	}
    //END
    CallFile.close(); 
	PutFile.close();
	rnd.SaveSeed();
 	return 0;
    
}