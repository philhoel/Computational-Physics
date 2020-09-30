#include <cstdlib>
#include <fstream>
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
        double omega_r;

        int p;
        int q;

        
        mat R;
        vec rho;
        vec anaEig;

    
        void fillMatrix_1();

        void fillMatrix_2();

        void fillMatrix_3();

        void fillR();


    public:

        const double PI = 3.1415926535897;

        mat A;

        vec eig;

        LinSys( int n );

        LinSys( int n, double rho_max );

        LinSys( int n, double rho_max, double omega );

        void offdiag( int n );

        void jacobi_rotate( int n );

        void iterations();

        void print_matrix();

        double get_maxnondiag();

        void extract_eigenvalues();

        void print_eigenvectors();

        void print_eigenvalues();

        void write_eig_to_file(string filename);

        void sort_eig();

        void pretty_print();

        void analyticEig();

        void print_anaEig();

};