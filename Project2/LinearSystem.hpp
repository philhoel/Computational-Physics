#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include "time.h"
#include <armadillo>

using namespace std;
using namespace arma;

class LinSys {

    private:

        double tol;
        int iter;
        int N;
        double h;
        double hh;
        double maxnondiag;
        int maxiter;

        int p;
        int q;

        mat A;
        mat R;
        vec rho;
        vec eig;

    
        void fillMatrix_1();

        void fillMatrix_2();


    public:

        LinSys( int n );

        LinSys( int n, int rho_max );

        void offdiag( int n );

        void jacobi_rotate( int n );

        void iterations( int n );

        void print_matrix();

        double get_maxnondiag();

        void extract_eigenvalues();

        void print_eigenvalues();

        void write_eig_to_file(string filename);

};