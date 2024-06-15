#include "Distribution.h"

Distribution::Distribution(function<double(Random*)> rand, function<double(double)> f): _rand(rand), _pdf(f) {}

function<double(double)> Distribution::F(){
    return _pdf;
}

function<double(Random*)> Distribution::Rand(){
    return _rand;
}