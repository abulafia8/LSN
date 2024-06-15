#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

#include "GenLib.h"
#include "RNG/random.h"
#include "RNG/GeneralPurposeLib.h"
// Crossover (forse meglio che con operatore)
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
// Crea variabile map (cerchio)
vector<vec> CreateMapCircle(){
    vector<vec> map;
    for (int i = 0; i < N; i++){
        double theta = (double)(2*M_PI*i)/(double)N;
        map.push_back({cos(theta), sin(theta)});
    }
    return map;
}
// Crea variabile map random su quadrato (sempre uguale)
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
vector<vec> CreateMapProv(){
    vector<vec> map;
    ifstream coords("../INPUT/cap_prov_ita.dat");
    double x; double y;
    for (int i = 0; i < N; i++){
        coords >> x; coords >> y;
        map.push_back({x, y});
    }
    return map;
}
// Vettore composto dagli elementi di vec1 che non sono in vec2
vector<int> VecDiff(vector<int> vec1, vector<int> vec2){
    unordered_set<int> set(vec2.begin(), vec2.end());
    vector<int> result;
    for (int c : vec1) 
        if (set.find(c) == set.end())
            result.push_back(c);
    return result;
}
// Primi n elementi di un std vector
vector<int> Cut(vector<int> vec, int n) {
    return vector<int>(vec.begin(), vec.begin() + n);
}
// Ordina gli indici in base alla lunghezza corrispondente (serve in Population::Sort())
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
// Stampa il percorso migliore in coordinate cartesiane
void PrintBest(Trip trip){
    ofstream OutFile("../OUTPUT/Best.dat");
    vector<int> t = trip.GetTrip();
    vector<vec> map = trip.GetMap();
    for (int i = 0; i < (int)t.size(); i++)
        OutFile << map[t[i]](0) << "\t" << map[t[i]](1) << endl;
}
// Crea file con punti città
void PrintMap(vector<vec> map){
    ofstream OutFile("../OUTPUT/Map.dat");
    for (int i = 0; i < (int)map.size(); i++)
        OutFile << map[i](0) << "\t" << map[i](1) << endl;
}
// Riarrangia casualmente i best appartententi a diversi continenti
void Shuffle(vector <int>& vec, int seed){  
    unsigned s = static_cast<unsigned>(seed);  
        mt19937 g(s);
        int size = (int)(vec.size() / N);
        //il best di perm[i] andrà nel contintente i
        vector <int> perm;
        for (int i = 0; i < size; i++)
            perm.push_back(i);
        shuffle(perm.begin(), perm.end(), g);
        //nuovo vettore con bests riarrangiati
        vector <int> new_vec(N * size);
        for (int i = 0; i < size; i++)
          for (int j = N*perm[i]; j < N*(perm[i]+1); j++){
            int k = j - N*perm[i];
            new_vec[i*N + k] = vec[j];
            //new_vec[i*N+k] = 0;
           }    
        vec = new_vec;
}
// Trova il percorso migliore fra quelli dei vari continenti
void BestAmongAll(Trip local_best, vector <int> global_best_trip, vector <vec> map, int size){
    double best_length = local_best.L();
    for (int i = 0; i < size; i++){
        Trip trip; trip.SetMap(map);
        vector<int> trip_temp(global_best_trip.begin() + i*N, global_best_trip.begin() + (i+1) * N);
        trip.SetTrip(trip_temp);
        double length = trip.L();
        if (length < best_length){
            best_length = length;
            local_best = trip;
        }
    }
    PrintBest(local_best);
    cout << "Best length: " << local_best.L() << endl;
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
