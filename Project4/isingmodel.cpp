#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <armadillo>
#include <mpi.h>

#include <time.h>

#include "isingmodel.hpp"

Ising::Ising(int N, double temp, bool r) {
    n = N;
    Grid = zeros<mat>(n,n);
    E = 0;
    M = 0;
    j = 1;
    T = temp;
    ran = r;
    acpt_count = 0;


    for (int de = -8; de <= 8; de++) {
        w[de+8] = 0;
    }

    for (int de = -8; de <= 8; de+=4) {
        w[de+8] = exp(-de/(T));
    }

    for (int i = 0; i < 5; i++) {
        average[i] = 0.;
    }

    if (ran) {
        initialize();
    } else {
        initialize_rand();
    }
}

// Periodic Boundary Conditions
int Ising::PBC(int i, int limit, int add) {
    return (i + limit + add) % (limit);
}

// Resets values in class
void Ising::reset() {
    E = 0;
    M = 0;
    if (ran) {
        initialize();
    } else {
        initialize_rand();
    }
}

// Initializes grid
// Initializes energy
void Ising::initialize() {

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            Grid(x,y) = 1;
            M += Grid(x, y);
        }
    }

    for(int y =0; y < n; y++) {
        for (int x= 0; x < n; x++){
            E -=  (double) Grid(y,x)*
	        (Grid(PBC(y,n,-1),x) +
	        Grid(y,PBC(x,n,-1)));
        }
    }
}

// Initializes grid at random
// Initializes energy
void Ising::initialize_rand() {

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (rand()%2 == 0) {
                Grid(x,y) = 1;
            } else {
                Grid(x,y) = -1;
            }
            M += Grid(x, y);
        }
    }

    for(int y =0; y < n; y++) {
        for (int x= 0; x < n; x++){
            E -=  (double) Grid(y,x)*
	        (Grid(PBC(y,n,-1),x) +
	        Grid(y,PBC(x,n,-1)));
        }
    }
}

// Metropolis
void Ising::Metropolis() {

    //std::default_random_engine generator;
    //std::uniform_real_distribution<double> dist(0.0, 1.0);

    int lim = n*n;
    for (int y = 0; y < lim; y++) {
        

        int ix = (int) (rand())%(n);
        int iy = (int) (rand())%(n);

        double g = double(rand())/(RAND_MAX);
        //cout << "g = " << g << endl;
    
        int dE = 2*Grid(iy, ix)*

        (Grid(iy, PBC(ix, n, -1))+

        Grid(PBC(iy, n, -1), ix) +

        Grid(iy, PBC(ix, n, 1))+

        Grid(PBC(iy, n, 1), ix));
        if ((double) rand()/RAND_MAX <= w[dE+8]) {
            Grid(iy,ix) *= -1;
            M += 2*Grid(iy, ix);
            E += dE;
            acpt_count++;
            //count_de.push_back(dE);
        }
    
    }
}

// Runs the Monte Carlo cycles with the
// metropolis function inside
void Ising::MonteCarlo(int mcs) {
    double norm = 1./mcs;
    for (int cycles = 1; cycles <= mcs; cycles++) {
        Metropolis();

        average[0] += E;
        average[1] += E*E;
        average[2] += M;
        average[3] += M*M;      
        average[4] += fabs(M);
    }
}

//brukes for oppgave d
void Ising::MonteCarlo(int mcs, bool d) {

    Eave = zeros<vec> (mcs);
    Mave = zeros<vec> (mcs);
    accept = zeros<vec> (mcs);
    double norm;
    double tol = 1e-2;
    bool firsttime = true;
    num_E = 0;

    for (int cycles = 1; cycles <= mcs; cycles++) {
        Metropolis();
        norm = 1./cycles;

        average[0] += E;
        Eave(cycles - 1) = average[0]*norm;
        average[1] += M;
        Mave(cycles - 1) = average[1]*norm;


        accept(cycles - 1) = acpt_count;
        //acpt_count = 0;

        if(cycles > 10000)
        {
            if( fabs(Eave(cycles-1)-Eave(cycles-2)) < tol )
            {
                //cout << "bajs =" << E << endl;
                count_de.push_back(E/(n*n));
                num_E++;

                if(firsttime)
                {
                    num_carlos = cycles;
                    firsttime = false;
                }
            }
        }
        

    }

}

void Ising::MonteCarloMPI(int mcs, int team) 
{
    int num_threads, my_rank;
    
    
    team = MPI_Comm_size (MPI_COMM_WORLD, &num_threads);
    team = MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

    //cout << "my rank " << my_rank << endl;

    int no_intervalls = mcs/num_threads;
    int my_begin = my_rank*no_intervalls + 1;
    int my_end = (my_rank+1)*no_intervalls;
    if ( (my_rank == num_threads-1) &&( my_end < mcs) ) my_end = mcs;

    double norm = 1.0/mcs;
    double tmp_average[5];

    team = MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    team = MPI_Bcast (&tmp_average, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int cycles = my_begin; cycles <= my_end; cycles++) 
    {
        Metropolis();
        
        tmp_average[0] += E;
        tmp_average[1] += E*E;
        tmp_average[2] += M;
        tmp_average[3] += M*M;      
        tmp_average[4] += fabs(M);

    }

    for(int i = 0; i < 5; i++)
    {
        //cout << "my_rank = " << my_rank << "tmpave = " << tmp_average[i] << endl;
        team = MPI_Reduce(&tmp_average[i], &average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    /*
    if(my_rank==0)
    {
        average[0] = average[0]*norm;
        average[1] = average[1]*norm;
        average[2] = average[2]*norm;
        average[3] = average[3]*norm;      
        average[4] = average[4]*norm;
        //cout << "average = " << average[0] << endl; 
    }
    */
    
}