#ifndef GeneralPurposeLib_h
#define GeneralPurposeLib_h

#include <vector>

#include "random.h"

using namespace std;

void Initialize (Random* rnd, int restart=0);
double MediaRandom (Random* r, int throws);
double MediaVarRandom (Random* r, int throws, double mean);
double MediaVector (double* vec, int n);
double MediaStdVec(vector<double> vec);
double MediaStdVec(vector<double> vec);
void EmptyVectorInt(int* vec, int n);
double Error (double a, double b, int n);
double Chi2 (int* counts, double mean, int intervals);
void Fill(int* counts, Random* r, int throws, int intervals);
double ExpICF(Random* r, double lambda);
double LorentzICF(Random* r, double gamma, double mu);
double MediaRandomExp (Random* r, int throws, double lambda);
double MediaRandomCauchy (Random* r, int throws, double gamma, double mu);



#endif
