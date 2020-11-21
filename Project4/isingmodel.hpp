#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

using namespace std;
using namespace arma;

#ifndef ISINGMODEL_HPP
#define ISINGMODEL_HPP

class Ising {

    public:
        
        mat Grid;

        double j;

        double E;
        
        double M;

        double T; // Temperature

        int n; // Grid size

        bool ran; // To run with random initializer or normal

        double w[17]; // Check weight for new config in metropolis

        double average[5];

        //vec Eave;
        //vec Mave;

        Ising(int N, double temp, bool r = true);

        int PBC(int i, int limit, int add);

        void reset();

        void initialize_rand();

        void initialize();

        void Metropolis();

        void MonteCarlo(int mcs);

        void MonteCarlo(int mcs, bool d);

        //void MonteCarlo(int mcs, bool d, double norm);

};
#endif