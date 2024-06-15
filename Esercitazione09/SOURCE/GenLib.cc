#include <unordered_set>
#include <string>

#include "GenLib.h"
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"

vector<Trip> CrossOver(Trip a, Trip b, Random* rnd){
    vector<vec> map = a.GetMap();

    vector<int> tripa = a.GetTrip();
    vector<int> tripb = b.GetTrip();
    int cut = (int)rnd->Rannyu(1, N-1);    
    vector<int> cuta = Cut(tripa, cut);   
    vector<int> cutb = Cut(tripb, cut);   
    
    vector<int> filla = VecDiff(tripb, cuta);
    vector<int> fillb = VecDiff(tripa, cutb);
    cuta.insert(cuta.end(), filla.begin(), filla.end());
    cutb.insert(cutb.end(), fillb.begin(), fillb.end());

    Trip new_tripa = Trip(map, rnd);
    new_tripa.SetTrip(cuta);
    Trip new_tripb = Trip(map, rnd);
    new_tripb.SetTrip(cutb);

    vector<Trip> result;
    result.push_back(new_tripa);
    result.push_back(new_tripb);

    return result;
}

vector<vec> CreateMapCircle(){
    vector<vec> map;
    for (int i = 0; i < N; i++){
        double theta = (double)(2*M_PI*i)/(double)N;
        map.push_back({cos(theta), sin(theta)});
    }
    return map;
}

vector<vec> CreateMapSquare(){
    vector<vec> map;
    Random rnd; Initialize(&rnd);
    for (int i = 0; i < N; i++){
        double x = rnd.Rannyu();
        double y = rnd.Rannyu();
        map.push_back({x, y});
    }
    return map;
}

vector<int> VecDiff(vector<int> vec1, vector<int> vec2){
    unordered_set<int> set(vec2.begin(), vec2.end());
    vector<int> result;
    for (int c : vec1) 
        if (set.find(c) == set.end())
            result.push_back(c);
    return result;
}

vector<int> Cut(vector<int> vec, int n) {
    return vector<int>(vec.begin(), vec.begin() + n);
}

vector<int> SortIndices(vector<double> vec){  
    vector<int> indices((int)vec.size());       
    for (int i = 0; i < (int)vec.size(); i++)
        indices[i] = i;
    //comparatore
    auto comparator = [&vec](int a, int b) {
        return vec[a] < vec[b];
    };
    sort(indices.begin(), indices.end(), comparator);
    return indices;
}

void PrintBest(Trip trip){
    ofstream OutFile("../OUTPUT/Best.dat");
    vector<int> t = trip.GetTrip();
    vector<vec> map = trip.GetMap();
    for (int i = 0; i < (int)t.size(); i++)
        OutFile << map[t[i]](0) << "\t" << map[t[i]](1) << endl;
}

void PrintMap(vector<vec> map){
    ofstream OutFile("../OUTPUT/Map.dat");
    for (int i = 0; i < (int)map.size(); i++)
        OutFile << map[i](0) << "\t" << map[i](1) << endl;
}

/*
vector<int> SortIndices(vector<Trip> vec){    
    vector<int> indices((int)vec.size());      
    for (int i = 0; i < (int)vec.size(); i++)
        indices[i] = i;
    //comparatore
    auto comparator = [&vec](int a, int b) {
        return vec[a].L() < vec[b].L();
    };

    sort(indices.begin(), indices.end(), comparator);
    return indices;
}
*/
