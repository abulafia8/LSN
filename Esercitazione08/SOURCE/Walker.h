#ifndef Walker_h
#define Walker_h

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#include <functional>
#include <string>
#include <vector>
#include <armadillo>
#include <string>

using namespace std;
using namespace arma;

const double STEP = 2.0;    //step transizione per metropolis ordinario
const double ASTEP = .35;   //step transizione per annealing

class Walker{
    public:
        Walker(Random* ra, vec start, function<double(vec, vec)> f, vec pars, int restart=0);

        vec GetX();
        double GetAcceptance();
        vector<vec> GetPath();
        int GetTimeStep();
        vec GetPars();
        std::function<double(vec, vec)> GetFunction();
        void SetPars(vec pars);
        void SetX(vec x);
        vec UniformT();
        void Move();
        void MoveAndTrack(string file);
        
    private:
        Random* _r;
        vec _x;
        int _dim;
        int _accepted;
        int _tot_steps;
        vec _pars;
        std::function<double(vec, vec)> _f;
        vector<vec> _path;

        vector<double> _H;
};

#endif




