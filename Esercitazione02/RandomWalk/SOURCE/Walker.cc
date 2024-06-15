#include <iostream>
#include <math.h>
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#include "Walker.h"

using namespace std;

//COSTRUTTORE DEFAULT
Walker::Walker():
_spacing (1.),
_lgt (0),
_x (.0),
_y (.0),
_z (.0),
r (NULL){}

//COSTRUTTORE 
Walker::Walker(double a, Random* ra):
_spacing (a),
_lgt (0),
_x (.0),
_y (.0),
_z (.0),
r (ra){}

//METODI GET
double Walker::GetX(){
    return _x;
}

double Walker::GetY(){
    return _y;
}

double Walker::GetZ(){
    return _z;
}

//METODI
void Walker::TakeDiscrStep(){
    //selezione verso (avanti o indietro)
    int verso;
    if (r->Rannyu() < .5)
        verso = 1;
    else
        verso = -1;
    //selezione direzione (x y z)
    double d = r->Rannyu();
    if (d < 1./3)
        _x += verso*1;
    else if(d > 1./3 && d < 2./3)
        _y += verso*1;
    else
        _z += verso*1;
    
    _lgt++;
}

void Walker::TakeContStep(){
    double phi = 2 * M_PI * r->Rannyu();
    double theta = acos(1 - 2 * r->Rannyu());
    double x = _spacing * sin(theta) * cos(phi); 
    double y = _spacing * sin(theta) * sin(phi); 
    double z = _spacing * cos(theta); 

    _x += x;
    _y += y;
    _z += z;

    _lgt++;
}

double Walker::GetDistanceSq(){
    double x2 = _x*_x;
    double y2 = _y*_y;
    double z2 = _z*_z;

    return _spacing * (x2 + y2 + z2);
}


