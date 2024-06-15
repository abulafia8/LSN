#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include "LibIntegration.h"

#include "Distribution.h"

#define M 1000000
#define N 100

using namespace std;

int main (int argc, char *argv[]){
	Random rnd;
	Initialize(&rnd);
	int L = M/N;

	Distribution uniform = Distribution(UniRand, UniPDF);
	Distribution linear = Distribution(LinICF, LinPDF);
	Distribution quadratic = Distribution(QuadTAC, QuadPDF);
	
	IntBlocks(rnd, N, L, uniform, "../OUTPUT/IntCosUni.dat");
	IntBlocks(rnd, N, L, linear, "../OUTPUT/IntCosLin.dat");
	IntBlocks(rnd, N, L, quadratic, "../OUTPUT/IntCosQuad.dat");
     
	rnd.SaveSeed();
 	return 0;
}


