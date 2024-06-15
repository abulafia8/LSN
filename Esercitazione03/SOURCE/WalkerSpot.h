#ifndef Walker_h
#define Walker_h

#include "RNG/random.h"

class WalkerSpot{
    public:
        WalkerSpot();
        WalkerSpot(double t, Random* ra);

        double GetS();
        void TakeStepSpot();

    private:
        double _s;
        double _t;
        int _lgt;
        Random* _r;
};

#endif