#ifndef GeneralPurposeLib_h
#define GeneralPurposeLib_h

#include "random.h"
#include <functional>

void Initialize (Random* rnd, int restart=0);
void InitializePar(Random* rnd, int rank);
double MediaRandom (Random* r, int throws);
double MediaVarRandom (Random* r, int throws, double mean);
double MediaBuffon(Random* r, int throws, double d, int nthr);
double MediaVector (double* vec, int n);
void EmptyVectorInt(int* vec, int n);
double Error (double a, double b, int n);
double Chi2 (int* counts, double mean, int intervals);
void Fill(int* counts, Random* r, int throws, int intervals);
double Uniform(Random* r, double* par);
double ExpICF(Random* r, double* par);
double LorentzICF(Random* r, double* par);
double Distributions(Random *r, int throws, std::function<double(Random*, double*)> f, double* par);
double Theta(Random* r);

double LinICF(Random* r);
double IntCosineUniform (Random* r, int throws);
double IntCosineTay(Random* r, int throws);
double IntCosineLin(Random* r, int throws);




#endif
