#include <math.h>

#include "WalkerSpot.h"
#include "RNG/random.h"

#define S0 100
#define R .1
#define VOLAT .25


using namespace std;

//COSTRUTTORE
WalkerSpot::WalkerSpot():
_s (.0),
_t (.0),
_lgt (0),
_r (NULL){}

WalkerSpot::WalkerSpot(double t, Random* ra):
_s (S0),
_t (t),
_lgt (0),
_r (ra){}

//METODI
double WalkerSpot::GetS(){
    return _s;
}

void WalkerSpot::TakeStepSpot(){
    double z = _r->Gauss(.0, 1.);
    _s = _s * exp( (R - .5 * VOLAT * VOLAT) * _t + VOLAT * z * sqrt(_t));
}


