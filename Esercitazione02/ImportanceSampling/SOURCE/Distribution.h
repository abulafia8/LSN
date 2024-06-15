#ifndef Distribution_h
#define Distribution_h

#include <functional>

#include "RNG/random.h"

using namespace std;

//Unisce la pdf e il generatore di numeri casuali distribuiti secondo tale pdf
class Distribution{
    private:
        function<double(Random*)> _rand;
        function<double(double)> _pdf;
    
    public:
        Distribution(function<double(Random*)> rand, function<double(double)> f);
        function<double(Random*)> Rand();
        function<double(double)> F();
};

#endif