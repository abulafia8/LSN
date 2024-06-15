#ifndef GenLib_h
#define GenLib_h

#include "Trip.h"
#include "Population.h"

vector<Trip> CrossOver(Trip a, Trip b, Random* rnd);
vector<vec> CreateMapCircle(); 
vector<vec> CreateMapSquare();
vector<int> VecDiff(vector<int> vec1, vector<int> vec2);
vector<int> Cut(vector<int> vec, int n);
vector<int> SortIndices(vector<double> vec);
void PrintBest(Trip trip);
void PrintMap(vector<vec> map);
//vector<int> SortIndices(vector<Trip> vec);

#endif