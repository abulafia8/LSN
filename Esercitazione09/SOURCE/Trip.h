#ifndef Trip_h
#define Trip_h

#include <vector>
#include <armadillo>

#include "RNG/random.h"

#define N 34

using namespace std;
using namespace arma;

class Trip{
    public:
        //Trip(vector<vec> map, int r=1);
        Trip(vector<vec> map, Random* rnd);
        Trip();
        vector<int> GetTrip();
        vector<vec> GetMap();
        void SetTrip(vector<int> trip);
        void SetMap(vector<vec> map);
        double L();
        bool Check();
        vec Map(int n);
        void PairPerm(Random* rnd);
        void Invert(Random* rnd);
        void Perm(Random* rnd);
        void Swap(Random* rnd);
        void Shift(Random* rnd);

    private:
        vector<int> _trip;
        vector<vec> _map;
};

#endif