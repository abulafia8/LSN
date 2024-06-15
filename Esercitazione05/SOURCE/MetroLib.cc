#include "MetroLib.h"

#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

// Funzioni analitiche per rappresentare stati
double Radius (double* x){
    return sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
}

double GroundState(double* x){
    double r = Radius(x);
    return exp(-2. * r);
}

double ExcState(double* x){
    double r = Radius(x);
    return exp(-r) * x[2] * x[2];   
}

// Fornisce media in un blocco per raggio 
double MediaMetroRadius(Walker* walker, int Length){
    double sum = 0;
    for (int i = 0; i < Length; i ++){
        walker->Move();
        double x[] = {walker->GetX()[0], walker->GetX()[1], walker->GetX()[2]};
        sum += Radius(x);
    }

    return sum / double(Length);   
}

// Inizializza i parametri del walker
void MetroInitialize(Params* params){
    ifstream input("../INPUT/input.dat");
    string stringa;
    string sottostringa;
    while (!input.eof())
    {
        input >> stringa;
        if (stringa == "T"){
            input >> sottostringa;
            if (sottostringa == "UNIFORM")
                params->step_type = "Uniform";
            else if (sottostringa == "GAUSSIAN")
                params->step_type = "Gaussian";
            else
                cerr << "In ../INPUT/input.dat : either UNIFORM or GAUSSIAN" << endl;
        }
        else if (stringa == "STEP")
            input >> params->step_width;
        else if (stringa == "FUNCTION"){
            input >> sottostringa;
            if (sottostringa == "GS"){
                params->f = GroundState;
                params->filename = "../OUTPUT/GroundState" + params->step_type + ".dat";
            }
            else if (sottostringa == "ES"){
                params->f = ExcState;
                params->filename = "../OUTPUT/ExcitedState" + params->step_type + ".dat";
            }
            else
                cerr << "In ../INPUT/input.dat : either GS or ES" << endl;
        }
        else if (stringa == "START"){
                input >> params->start[0];
                input >> params->start[1];
                input >> params->start[2];
            }    
        else if (stringa == "ENDINPUT")
            break;
    }
    input.close();
}
