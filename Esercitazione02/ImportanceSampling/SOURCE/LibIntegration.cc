#include "LibIntegration.h"
#include "RNG/GeneralPurposeLib.h"

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

// Procedono accoppiate funzioni per generare campioni sencondo una certa pdf
// e la relativa forma funzionale
double UniRand(Random* r){
	return r->Rannyu();
}

double UniPDF(double x){
	if (x >= 0 or x < 1) return 1;
	else return 0;
}

double LinICF(Random* r){
	return 1 - sqrt(1 - r->Rannyu());
}

double LinPDF(double x){
	return 2*(1 - x);
}

double QuadPDF(double x){
	return 1.5 * (1 - x*x);
}

double QuadTAC(Random* r){
	double x, y;
	do{
		x = r->Rannyu();
		y = .5*M_PI*r->Rannyu();
	} while (y > .5*M_PI*(1. - x*x));
	return x;
}

// Integra con IS, accettando come argomento la struct Distribution
// (che spilla insieme generatore e relativa forma funzionale)
double Integrate(Random* r, int throws, Distribution d){
	function <double(double)> f = d.F();
	function <double(Random*)> rand = d.Rand();
	double sum = 0;
	double y;
	for (int i = 0; i < throws; i++){
		y = rand(r);
		sum += .5*M_PI*cos(.5*M_PI*y) / f(y);
	}
	sum /= throws;
	return sum;
}

// Fa medie a blocchi e stampa in file
void IntBlocks(Random rnd, int N, int L, Distribution d, string filename){
	ofstream OutFile(filename);
	vector<double> stoch;
	vector<double> stoch2;
	vector<double> prog_avg;
	vector<double> prog_avg2;

	for (int i = 0; i < N; i++){
		stoch.push_back(Integrate(&rnd, L, d));
		stoch2.push_back(stoch[i]*stoch[i]);
		
		prog_avg.push_back(MediaStdVec(stoch));
		prog_avg2.push_back(MediaStdVec(stoch2));
		double err_prog = Error(prog_avg2[i], prog_avg[i], i);
		
		OutFile << prog_avg[i] << "\t" << err_prog << endl;
	}

	OutFile.close();
}


