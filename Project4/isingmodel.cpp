#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <armadillo>

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

    for (int de = -8; de <= 8; de++) {
        w[de+8] = 0;
    }

    for (int de = -8; de <= 8; de+=4) {
        w[de+8] = exp(-de/T);
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

    for (int x = 0; x < n; x++) {
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

    for (int x = 0; x < n; x++) {
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

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {

            int ix = (int) (rand())%(n);
            int iy = (int) (rand())%(n);
        
            int dE = 2*Grid(iy, ix)*
            (Grid(iy, PBC(ix, n, -1))+
            Grid(PBC(iy, n, -1), ix) +
            Grid(iy, PBC(ix, n, 1))+
            Grid(PBC(iy, n, 1), ix));


            if ((int) rand()%n <= w[dE+8]) {
                Grid(iy,ix) *= -1;
                M += 2*Grid(iy, ix);
                E += dE;
            }
        }
    }
}

// Runs the Monte Carlo cycles with the
// metropolis function inside
void Ising::MonteCarlo(int mcs) {

    for (int cycles = 1; cycles <= mcs; cycles++) {
        Metropolis();
        average[0] += E;
        average[1] += E*E;
        average[2] += M;
        average[3] += M*M;
        average[4] += fabs(M);

        reset();
    }
}