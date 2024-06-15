#include "Population.h"
#include "Trip.h"
#include "GenLib.h"
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
#include <algorithm>
#include <fstream>

Population::Population(Random* ra, int n, vector<vec> map): _r(ra), _n(n){
    for(int i = 0; i < n; i++){
        Trip trip = Trip(map, _r);
        _pop.push_back(trip); 
    } 
    this->Sort();   
    _best.SetMap(map);
    _best.SetTrip(_pop[0].GetTrip());
    ofstream FileLengths("../OUTPUT/Lengths.dat");
    FileLengths.close();
}

vector<Trip> Population::GetPop(){
    return _pop;
}

int Population::GetN(){
    return _n;
}

void Population::Sort(){
    vector<double> lengths;
    for (int i = 0; i < _n; i++)
        lengths.push_back(_pop[i].L());
    vector<int> indices = SortIndices(lengths);
    vector<Trip> new_pop;
    for (int i = 0; i < _n; i++)
        new_pop.push_back(_pop[indices[i]]);
    _pop = new_pop;
}

void Population::Generation(){
    vector<Trip> new_pop;
    int i;
    int p = 5.5; 

    for (int j = 0; j < _n / 2; j++){
        //seleziona due individui
        i = (int)(_n *pow(_r->Rannyu(), p));
        Trip t1 = _pop[i];
        i = (int)(_n *pow(_r->Rannyu(), p));
        Trip t2 = _pop[i];
        //fanno crossover (forse)
        if (_r->Rannyu() < .75){
            vector<Trip> offspring = CrossOver(t1, t2, _r);
            t1 = offspring[0];
            t2 = offspring[1];
        }
        //mutazioni
        if (_r->Rannyu() < .1){
            t1.PairPerm(_r);
        }
        if (_r->Rannyu() < .1){
            t2.PairPerm(_r);
        }
        if (_r->Rannyu() < .13){
            t1.Invert(_r);
        }
        if (_r->Rannyu() < .13){
            t2.Invert(_r);
        }
        if (_r->Rannyu() < .2){
            t1.Perm(_r);
        }
        if (_r->Rannyu() < .2){
            t2.Perm(_r);
        }
        if (_r->Rannyu() < .1){
            t1.Shift(_r);
        }
        if (_r->Rannyu() < .1){
            t2.Shift(_r);
        }
        //aggiunta a nuova popolazione
        if (t1.Check() == false or t2.Check() == false)
            std::cout << "errore" << endl;
        new_pop.push_back(t1);
        new_pop.push_back(t2);
    }
    _pop = new_pop;

    this->Sort();
    _best.SetTrip(_pop[0].GetTrip());
    std::cout << _pop[0].L() << endl;

    ofstream FileLengths;
    FileLengths.open("../OUTPUT/Lengths.dat", ios::app);
    FileLengths << _pop[0].L() << "\t\t\t\t" << this->AvgHalf() << endl;
    FileLengths.close();
}

Trip Population::GetBest(){
    return _best;
}

double Population::AvgHalf(){
    double sum = 0;
    for (int i = 0; i < _n / 2; i++){
        sum += _pop[i].L();
    }
    return sum / (_n/2);
}




/*
void Population::Sort(){
    vector<int> indices = SortIndices(_pop);
    vector<Trip> new_pop;
    for (int i = 0; i < _n; i++)
        new_pop.push_back(_pop[indices[i]]);
    _pop = new_pop;
}
*/



