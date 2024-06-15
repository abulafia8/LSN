#include <iostream>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "Walker.h"
#include "MetroLib.h"

Walker::Walker(Random* ra, Params params, int restart): 
_r(ra),
_x(params.start), 
_step(params.step_width),
_accepted(0), 
_tot_steps(0){
    Initialize(_r, restart);
    _f = params.f;
    _dim = DIM;
    _step_type = params.step_type;
    for (int i = 0; i < _dim; i++)
         _path.push_back(_x[i]);
}

double* Walker::GetX(){
    return _x;
}

void Walker::SetX(double* x){
    for (int i = 0; i < _dim; i++)
        _x[i] = x[i];
}

double* Walker::UniformT(){
    double* pos = new double[_dim];
    for(int i = 0; i < _dim; i++)
        pos[i] = _x[i] + _r->Rannyu(-_step, _step);
    return pos;
}

double* Walker::GaussianT(){
    double* pos = new double[_dim];
    for (int i = 0; i < _dim; i++)
        pos[i] = _r->Gauss(_x[i], _step);
    return pos;
}

void Walker::Move(){
    double* x_new = NULL;
    if (_step_type == "Uniform")
        x_new = UniformT();
    if (_step_type == "Gaussian")
        x_new = GaussianT();
    double alpha = min(1., _f(x_new) / _f(_x));
    double r = _r->Rannyu();
    if (r < alpha){
        SetX(x_new);
        _accepted++;
    }
   for (int i = 0; i < _dim; i++)
        _path.push_back(_x[i]);
    _tot_steps++;
}

double Walker::GetAcc(){
    return double(_accepted) / double(_tot_steps);
}

void Walker::ResetAcc(){
    _accepted = 0;
    _tot_steps = 0;
}

vector<double> Walker::GetPath(){
    return _path;
}
//Stampare strada facendo sembra essere più lento
void Walker::PrintPath(){
    string filename;
    double zero[] = {.0, .0, .0};
    if (_f(zero) == 1.)
        filename = "../OUTPUT/PathGroundState"+_step_type+".dat";
    if (_f(zero) == .0)
        filename = "../OUTPUT/PathExcitedState"+_step_type+".dat";
    ofstream Path(filename);
    for (int i = 0; i < (int)_path.size(); i++){
        if ((int)(i+1) % 3 == 0)
            Path << _path[i] << endl;
        else
            Path << _path[i] << setw(23);
    }
}