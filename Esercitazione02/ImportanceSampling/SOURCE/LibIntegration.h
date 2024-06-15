#ifndef LibIntegration_h
#define LibIntegration_h

#include "RNG/random.h"
#include "Distribution.h"
#include <functional>
#include <string>

using namespace std;

//Libreria contenente:
//Generatori random secondo alcune distribuzioni
//Forma funzionale della relativa pdf
//Funzione che integra il coseno con importance sampling
// Funzione che calcola e stampa in un file risultati
double UniRand(Random* r);
double UniPDF(double x);
double LinICF(Random* r);
double LinPDF(double x);
double QuadTAC(Random* r);
double QuadPDF(double x);

double Integrate(Random* r, int throws, Distribution d);
void IntBlocks(Random rnd, int N, int L, Distribution d, string filename);

#endif

