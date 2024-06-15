#ifndef Pop_h
#define Pop_h

#include "Trip.h"

class Population{
    public:
        Population(Random* ra, int n, vector<vec> map);
        vector<Trip>& GetPop();
        int GetN();
        void Sort();
        void Generation();
        Trip GetBest();
        void SetBest(Trip best);
        double AvgHalf();
        
        //vector<Trip> _pop;
    
    private:
        Random* _r;
        vector<Trip> _pop;
        int _n;
};

#endif