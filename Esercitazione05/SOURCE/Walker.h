#ifndef Walker_h
#define Walker_h

#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#include <functional>
#include <string>
#include <vector>

#define DIM 3

using namespace std;


struct Params{
    string step_type;
    double step_width;
    function<double(double*)> f;
    string filename;
    double start[DIM];
};

class Walker{
    public:
        Walker(Random* ra, Params params, int restart=0);

        double* GetX();
        void SetX(double* x);
        double* UniformT();
        double* GaussianT();
        void Move();
        double GetAcc();
        void ResetAcc();
        vector<double> GetPath();
        void PrintPath();

    private:
        Random* _r;
        double* _x;
        double _step;
        int _accepted;
        int _tot_steps;
        function<double(double*)> _f;
        vector<double> _path;
        int _dim;
        string _step_type;
};

#endif