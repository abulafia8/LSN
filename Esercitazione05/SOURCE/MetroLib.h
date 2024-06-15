#ifndef MetroLib_h
#define MetroLib_h

#include "Walker.h"

using namespace std;

double Radius (double* x);       
double GroundState(double* x);  
double ExcState(double* x);
double MediaMetroRadius(Walker* walker, int Length);  
void MetroInitialize(Params* params);

#endif