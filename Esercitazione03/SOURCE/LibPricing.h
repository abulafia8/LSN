#ifndef LibPricing_h
#define LibPricing_h

#include "RNG/random.h"
#include "WalkerSpot.h"

double Profit(double spot, double rate, char type);
double Spot(double mu, double time, Random* w);
double MediaProfitDir(char type, int throws, Random* w);
double MediaProfitWalk(WalkerSpot* prt, int block_index, int block_size, char type);
double MediaDistSpot(WalkerSpot* prt, int block_index, int block_size);

#endif
