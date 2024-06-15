#include <unordered_set>
#include "Trip.h"
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

#include <armadillo>
#include <algorithm>

using namespace arma;

//COSTRUTTORI
Trip::Trip(vector<vec> map, Random* rnd): _map(map){
    unordered_set<int> seen;
    int a;
    _trip.push_back(0);
    for (int i = 1; i < N; i++){
        while(true){
            a = (int)((N-1)*rnd->Rannyu()) + 1;
            if (seen.find(a) == seen.end()){
                seen.insert(a);
                break;
            }
        }
        _trip.push_back(a);
    }
}

Trip::Trip(){
    for (int i = 0; i < N; i++)
        _trip.push_back(0);
    vector<vec> map;
    map.push_back({.0});
}

//GET E SET
vector<int> Trip::GetTrip(){
    return _trip;
}
vector<vec> Trip::GetMap(){
    return _map;
}
void Trip::SetTrip(vector<int> trip){
    _trip = trip;
}
void Trip::SetMap(vector<vec> map){
    _map = map;
}

//METODI, MUTAZIONI
double Trip::L(){
    double sum = 0;
    for (int i = 0; i < N-1; i++)
        sum += arma::norm(Map(_trip[i]) - Map(_trip[i+1]));
    sum += arma::norm(Map(_trip[N-1]) - Map(_trip[0]));
    return sum;
}
//la prima deve essere 0, le città sono tutte diverse, le città sono visitate tutte
bool Trip::Check(){
    unordered_set<int> seen;
    if (_trip[0] != 0)
        return false;
    for (int i = 0; i < N; i++){
        if (seen.find(_trip[i]) != seen.end())
            return false;
        seen.insert(_trip[i]);
    }
    if (accumulate(_trip.begin(), _trip.end(), 0) != .5*(N-1)*N)
        return false;
    return true;
}
//converte l'indice in trip in una posizione sulla carta
vec Trip::Map(int n){
    return {_map[n](0), _map[n](1)};
}
//mutazioni
void Trip::PairPerm(Random* rnd){
    int i = (int)rnd->Rannyu(1, N-1); 
    swap(_trip[i], _trip[i+1]);
}

void Trip::Invert(Random* rnd){
    int n = (int)rnd->Rannyu(1, N-1);   
    reverse(_trip.begin() + 1, _trip.begin() + n - 1);  
}

void Trip::Perm(Random* rnd){                
    int n = (int)rnd->Rannyu(1, N/2);
    vector<int> vec1;
    for (int i = 1; i < n; i++){
        vec1.push_back(_trip[i]);
    }
    vector<int> vec2;
    vec2.push_back(0);
    for (int i = n; i < 2*n-1; i++){
        vec2.push_back(_trip[i]);
    }
    vector<int> vec3;
    for (int i = 2*n-1; i < N; i++){
        vec3.push_back(_trip[i]);
    }
    //vec2.insert(vec2.end(), vec1.begin(), vec1.end());
    //vec2.insert(vec2.end(), vec3.begin(), vec3.end());
    vec2.insert(vec2.end(), vec3.begin(), vec3.end());
    vec2.insert(vec2.end(), vec1.begin(), vec1.end());

    _trip = vec2;
}

void Trip::Swap(Random* rnd){
    int n = (int)rnd->Rannyu(1, N/2);
    int m = (int)rnd->Rannyu(N/2, N);
    swap(_trip[n], _trip[m]);
}

void Trip::Shift(Random* rnd){
    int n = fabs((int)rnd->Rannyu(1, N));
    //int m = (int)rnd.Rannyu(1, N-1);
    for (int i = 1; i < N; i++){
        if (_trip[i] + n > N-1)
            _trip[i] = _trip[i] + n - (N-1);
        else
            _trip[i] = _trip[i] + n;
    }
}