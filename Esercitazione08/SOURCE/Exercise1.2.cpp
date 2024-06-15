#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "Walker.h"
#include "Lib.h"

using namespace std;

int main (int argc, char *argv[]){
    //PREP
    Random rnd;
    vec start = {.1, 1.};  
    vec beta = {1.};
    double beta_step = 1.5;
    Walker metroa = Walker(&rnd, start, Boltzmann, beta);
    ofstream Energies("../OUTPUT/Energies.dat");
    ofstream Parameters("../OUTPUT/Parameters.dat");
    //Annealing
    for (int j = 0; j < 200; j++){          
        for (int i = 0; i < 10; i++){          
            //metroa.Move();                   
            metroa.MoveAndTrack("../OUTPUT/Energies.dat");
            Parameters << metroa.GetX()[0] << setw(18) << metroa.GetX()[1] << endl;
        }
        metroa.SetPars(metroa.GetPars() + beta_step);
        cout << "Step " << j+1 << " / " << 200 << endl;
    }
    //A T fissata ottenere stima su parametri finali
    vector <double> mu;
    vector <double> sigma;
    for (int i = 0; i < 2500; i++){
        metroa.Move();
        mu.push_back(metroa.GetX()[0]);
        sigma.push_back(metroa.GetX()[1]);
        if (i%25 == 0)
            cout << i << "/" << 2500 << endl;
    }
    double ext_mu = MediaStdVector(mu); double err_mu = StdDev(mu, 250);
    double ext_sigma = MediaStdVector(sigma);   double err_sigma = StdDev(sigma, 250);
    //FINE
    ofstream FinalPars("../INPUT/InitialParameters.dat");
    FinalPars << ext_mu << "\t\t" << err_mu << endl;
    FinalPars << ext_sigma << "\t\t" << err_sigma << endl;
    Energies.close();
    Parameters.close();
    FinalPars.close();
    rnd.SaveSeed();
 	return 0;
}











