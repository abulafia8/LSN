#ifndef Walker_h
#define Walker_h

#include "RNG/random.h"

class Walker
{
    public:
        Walker();
        Walker(double a, Random* ra);

        double GetX();
        double GetY();
        double GetZ();

        void TakeDiscrStep();
        void TakeContStep();
        double GetDistanceSq();
        
    private:
        double _spacing;
        int _lgt;
        double _x;
        double _y;
        double _z;
        Random* r;
};

#endif