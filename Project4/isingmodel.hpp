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

        int n;

        Ising(int N);

        int PBC(int i, int limit, int add);

        void Metropolis();

        void WriteToFile();



};
#endif