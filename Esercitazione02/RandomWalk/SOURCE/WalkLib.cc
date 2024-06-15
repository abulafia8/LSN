#include <iostream>
#include <math.h>
#include <fstream>
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#include "Walker.h"
#include "WalkLib.h"

using namespace std;

double MediaDistBlock(Walker* prt, int block_index, int block_size){
	double sum = 0;
	for (int i = block_index * block_size; i < block_size * (block_index + 1); i++)
		sum+= prt[i].GetDistanceSq();	
	
	sum /= block_size;
	return sqrt(sum);
}

