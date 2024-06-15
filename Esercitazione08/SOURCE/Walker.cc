#include <iostream>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>

#include "Walker.h"
#include "RNG/GeneralPurposeLib.h"

#include "Lib.h"


Walker::Walker(Random* ra, vec start, function<double(vec, vec)> f, vec pars, int restart): 
_r(ra),
_x(start),
_accepted(0), 
_tot_steps(0),
_pars(pars) {
    Initialize(_r, restart);
    _f = f;
    _dim = _x.n_elem;     
    _H = {.0, .0};
    if (_dim == 2)
        _H = H(_x);       
} 

vec Walker::UniformT(){
    vec pos(_dim);
    double step = 0;
    if (_dim == 1)
        step = STEP;
    if (_dim == 2)
        step = ASTEP;
    for (int i = 0; i < _dim; i++)
        pos(i) = _x(i) + _r->Rannyu(-step, step);
    return pos;
}

void Walker::Move(){
    _path.push_back(_x);
    _tot_steps++;
    vec x_new = this->UniformT();
    double alpha = min(1., pow(_f(x_new, _pars), 2) / pow(_f(_x, _pars), 2));
    double r = _r->Rannyu();
    if (r < alpha){
        SetX(x_new);
        _accepted++;
    }
}

// Funzione usata esclusivamente per fare simulated annealing ma che
// sfrutta la struttura del walker Metropolis
void Walker::MoveAndTrack(string file){
    _path.push_back(_x);
    _tot_steps++;
    ofstream File(file, ios::app);
    vec x_new = this->UniformT();
    vector<double> H_new = H(x_new);
    double h = _H[0];   double h_new = H_new[0];   
    double err = _H[1];   double  err_new = H_new[1];
    
    double alpha = min(1., exp(-_pars[0]*(h_new - h)));
    double r = _r->Rannyu();
    if (r < alpha){
        SetX(x_new);
        _H = H_new;
        _accepted++;
        File << h_new << setw(30) << err_new << setw(30) << _pars[0] << endl;
    }
    else
        File << h << setw(30) << err << setw(30) << _pars[0] << endl;
    File.close();
}

double Walker::GetAcceptance(){
    return double(_accepted) / double(_tot_steps);
}

vector<vec> Walker::GetPath(){
    return _path;
}

int Walker::GetTimeStep(){
    return _tot_steps;
}

std::function<double(vec, vec)> Walker::GetFunction(){
    return _f;
}

void Walker::SetPars(vec pars){
    _pars = pars;
}

vec Walker::GetPars(){
    return _pars;
}

vec Walker::GetX(){
    return _x;
}

void Walker::SetX(vec x){
    _x = x;
}

