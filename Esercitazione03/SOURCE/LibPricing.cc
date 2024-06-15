#include <iostream>
#include <fstream>
#include <cmath>

#include "LibPricing.h"
#include "WalkerSpot.h"

#define M 100000
#define N_BLOCKS 100

#define S0 100
#define T 1
#define K 100
#define R .1
#define VOLAT .25

using namespace std;
// COMUNE A ENTRAMBI I CASI: PROFITTO
double Profit(double spot, char type){
	if( type == 'c')
		return exp(-R*T) * (max(.0, spot - K));
	else if(type == 'p')
		return exp(-R*T) * (max(.0, K - spot));		
	else{
		cerr << "PROBLEM: either enter 'c' or 'p' " << endl;
		return 0;
	}		
}
// FUNZIONI PER STIMA TRAMITE CAMPIONAMENTO DIRETTO
double Spot(Random* w){
	double wie = w->Gauss(0, T);
	return S0 * exp((R - .5*VOLAT*VOLAT) * T + VOLAT*wie);
}

double MediaProfitDir(char type, int throws, Random* w){
	double sum = 0;
	double spot;
	for (int i = 0; i < throws; i++){
		spot = Spot(w);
		sum += Profit(spot, type);
	}
	return sum/throws;
}
// FUNZIONI PER STIMA TRAMITE CAMMINO
double MediaProfitWalk(WalkerSpot* prt, int block_index, int block_size, char type){
	double sum = 0;
	for (int i = block_index * block_size; i < block_size * (block_index + 1); i++)
		sum += Profit(prt[i].GetS(), type);
	sum /= block_size;
	return sum;
}

double MediaDistSpot(WalkerSpot* prt, int block_index, int block_size){
	double sum = 0;
	for (int i = block_index * block_size; i < block_size * (block_index + 1); i++)
		sum+= prt[i].GetS() * prt[i].GetS();	
	sum /= block_size;
	return sqrt(sum);
}




