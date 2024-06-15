#include <iostream>
#include <fstream>
#include "Trip.h"
#include "GenLib.h"
#include "RNG/GeneralPurposeLib.h"
#include "RNG/random.h"
#include "Population.h"

int main (int argc, char *argv[]){
    //PREP
    Random rnd; Initialize(&rnd);  
    string type = argv[1];
    vector <vec> map;
    if (type == "Circle")
        map = CreateMapCircle();
    if (type == "Square")
        map = CreateMapSquare();
    PrintMap(map);
    //BODY
    int n = 3000;
    int n_gen = 200;
    Population pop = Population(&rnd, n, map);
    for (int i = 0; i < n_gen; i++){
        pop.Generation();
    }
    //WRAP UP
    PrintBest(pop.GetBest());
    rnd.SaveSeed();
    return 0;
}
