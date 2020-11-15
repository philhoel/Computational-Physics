#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <armadillo>

#include "isingmodel.hpp"

Ising::Ising(int N) {
    n = N;
    Lattice = zeros<mat>(n,n);
}

int Ising::PBC(int i, int limit, int add) {
    return (i + limit + add) % (limit);
}

void Ising::Metropolis() {

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {

            int ix;
            int iy;

            int dE = 2*Grid[yi][xi]*
            (Grid(iy, PBC(ix, n, -1))+
            Grid(PBC(iy, n, -1), ix) +
            Grid(iy, PBC(ix, n, 1))+
            Grid(PBC(iy, n, 1), ix));

        }
    }
}