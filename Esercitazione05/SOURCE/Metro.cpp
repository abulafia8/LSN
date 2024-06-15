#include <fstream>
#include <iomanip>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "Walker.h"
#include "MetroLib.h"

#define M 1000000
#define N 100

using namespace std;

int main (int argc, char *argv[]){
    //PREP
    Params par;
    MetroInitialize(&par);
    ofstream RadiusFile(par.filename);
    Random rnd;
    Walker walker = Walker(&rnd, par);

    double stoch[N];
	double stoch2[N];
	double prog_avg[N];
	double prog_avg2[N];
    double err_prog[N];
	int L = M/N; 
    //CALCOLO
    for (int i = 0; i < .5*L; i++)
        walker.Move();
    walker.ResetAcc();

    for (int i = 0; i < N; i++){
		stoch[i] = MediaMetroRadius(&walker, L);
		stoch2[i] = stoch[i]*stoch[i];
		
		prog_avg[i] = MediaVector(stoch, i+1); 
		prog_avg2[i] = MediaVector(stoch2, i+1);   
		err_prog[i] = Error(prog_avg2[i], prog_avg[i], i);
		RadiusFile <<prog_avg[i]<<setw(18)<<err_prog[i]<<setw(18)<<walker.GetAcc()<< endl;
	}
    //CHIUSURA
    walker.PrintPath();
    RadiusFile.close();
    rnd.SaveSeed();
 	return 0;
}




    