#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <mpi.h>
#include "GA/Trip.h"
#include "GA/GenLib.h"
#include "GA/RNG/GeneralPurposeLib.h"
#include "GA/RNG/random.h"
#include "GA/Population.h"

using namespace std;

int main(int argc, char *argv[]){
    
    // PREP
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = 300;
    int n_gen = 1605;
    int N_migr = 25;
    ofstream FileLengths("../OUTPUT/Lengths" + to_string(rank) + ".dat");
    string type = argv[1];
    vector<vec> map = CreateMapProv();
    if (rank == 0)
        PrintMap(map);
    Random rnd;
    InitializePar(&rnd, rank);
    Population pop = Population(&rnd, n, map);
    pop.Sort();



    // RUN THE GENETIC ALGORITHM
    for (int i = 0; i < n_gen; i++){
        pop.Generation();
        pop.Sort();
        
        if (type == "Migrations" && i % N_migr == 0 and i != 0){
            // Prendere il migliore individuo per ogni core
            Trip local_best = pop.GetBest();
            vector<int> local_best_trip = local_best.GetTrip();
            vector<int> global_best_trip(N * size);
            // Riunirli tutti in global_best e mischiarli
            MPI_Gather(local_best_trip.data(), N, MPI_INT, global_best_trip.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
            if (rank == 0)
                Shuffle(global_best_trip, i); // Assegnazione random ai vari continenti (con seme i)
            //MPI_Barrier(MPI_COMM_WORLD);
            // Migrazione
            MPI_Scatter(global_best_trip.data(), N, MPI_INT, local_best_trip.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
            //MPI_Barrier(MPI_COMM_WORLD);
            Trip trip(local_best_trip, map);  
            // Rimpiazza il proprio best con quello di altra pop
            pop.SetBest(trip);
            pop.Sort();
        }
        
        FileLengths << pop.GetBest().L() << "\t\t\t\t" << pop.AvgHalf() << endl;
        
        if (rank == 0)
            cout << "Generation " << i+1 << " of " << n_gen << endl;            
    }



    // FIND THE BEST AMONG THE CORES
    Trip local_best = pop.GetBest();
    vector<int> local_best_trip = local_best.GetTrip();
    vector<int> global_best_trip(N * size);
    MPI_Gather(local_best_trip.data(), N, MPI_INT, global_best_trip.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
        BestAmongAll(local_best, global_best_trip, map, size);
    


    //END
    FileLengths.close();
    MPI_Finalize();
    rnd.SaveSeed();
    return 0;
}

