#ifndef Lib_h
#define Lib_h

#include "Walker.h"
#include "RNG/random.h"
#include <armadillo>

double MediaStdVector(vector<double> vector);
double StdDev(vector<double> v, int bl_size);

double Gaussian (double x, double mu, double sigma);
double PsiTrial (vec x, vec pars);          //Funzione campionabile (da questo algoritmo)
double DoubleWell (double x);

double Hamiltonian (vec x, vec pars, function<double(vec, vec)> f);
double MediaHamiltonian (Walker* walker, int Length); 
vector<double> H (vec x);
double Boltzmann(vec x, vec y);         //Funzione campionabile (da questo algoritmo)

#endif