#ifndef GeneralPurposeLib_h
#define GeneralPurposeLib_h

#include "random.h"
#include <functional>
#include <vector>

void Initialize (Random* rnd, int restart=0);
double MediaVector (double* vec, int n);
double Error (double a, double b, int n);


#endif
