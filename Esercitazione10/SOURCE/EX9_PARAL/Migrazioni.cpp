#include <iostream>
#include <fstream>
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
    int n_gen = 200;
    int N_migr = 50;
    vector<vec> map = CreateMapSquare();
    if (rank == 0)
        PrintMap(map);
    Random rnd;
    InitializePar(&rnd, rank);
    Population pop = Population(&rnd, n, map);
    pop.Sort();
    ofstream FileLengths("../../OUTPUT/Lengths" + to_string(rank) + ".dat");



    // RUN THE ALGORITHM
    for (int i = 0; i < n_gen; i++){
        pop.Generation();
        pop.Sort();
        if (i % N_migr == 0 and i != 0){
            // Prendere il migliore individuo per ogni core
            Trip local_best = pop.GetBest();
            vector<int> local_best_trip = local_best.GetTrip();
            vector<int> global_best_trip(N * size);
            // Riunirli tutti in blobal_best e mischiarli
            MPI_Gather(local_best_trip.data(), N, MPI_INT, global_best_trip.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
            if (rank == 0)
                Shuffle(global_best_trip, i); // Assegnazione random ai vari continenti (con seme i)
            MPI_Barrier(MPI_COMM_WORLD);
            // Migrazione
            MPI_Scatter(global_best_trip.data(), N, MPI_INT, local_best_trip.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            Trip trip(local_best_trip, map);  
            // Inserisce il best di un altro core in cima alla propria pop
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