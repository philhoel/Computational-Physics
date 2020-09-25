#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include "time.h"
#include <armadillo>
#include "LinearSystem.hpp"


using namespace std;
using namespace arma;

    /*
    Fills the matrix with 2's down the diagonal
    and -1's one line above and under the diagonal
    */
    void LinSys::fillMatrix_1() {

        for ( int i = 1; i < N; i++ ) {

            A(i,i) = 2/hh;
            A(i, i-1) = -1/hh;
            A(i-1, i) = -1/hh;
        }

        A(0,0) = 2/hh;
    }

    void LinSys::fillMatrix_2() {

        for ( int i = 1; i < N; i++ ) {

            A(i,i) = 2/hh + pow(rho[i], 2);
            A(i, i-1) = -1/hh;
            A(i-1, i) = -1/hh;
        }

        A(0,0) = 2/hh + pow(rho[0], 2);

    }

    /*
    Constructor for LinSys class

    Parameter:
        int n - size of matrix
        bool b_or_d - chooses wether to use fillMatrix_1() or
                      fillMatrix_2(), dependent on what the matrix
                      should be filled with. True for for fillMatrix_1()
                      and False for fillMatrix_2()
    */
    LinSys::LinSys( int n ) {

        tol = 1.0E-10;
        iter = 0;
        N = n;
        h = 1./N;
        hh = pow(h,2);
        maxiter = 1E6;
        maxnondiag = 1;

        A = zeros<mat> (n, n);
        R = zeros<mat> (n, n);
        eig = zeros<vec> (n, 1);

        fillMatrix_1();

    }

    // Second contructor
    LinSys::LinSys( int n, int rho_max ) {

        tol = 1.0E-10;
        iter = 0;
        N = n;
        h = 1./N;
        hh = pow(h,2);
        maxiter = 1E6;
        maxnondiag = 1;

        A = zeros<mat> (n, n);
        R = zeros<mat> (n, n);
        eig = zeros<vec> (n, 1);

        rho = linspace(0, rho_max, N);

        fillMatrix_2();

    }

    /*
    Finds the biggest non-diagonal number in the matrix.
    Parameters:
        int n - number of iterations
    */
    void LinSys::offdiag( int n ) {

        double max;
        for ( int i = 0; i < n; i++ ) {

            for ( int j = i+1; j < n; j++ ) {

                double aij = fabs( A(i,j) );

                if ( aij > max ) {

                    max = aij;
                    p = i;
                    q = j;
                }
            }
        }

        maxnondiag = max;

        //cout << maxnondiag << endl;
    }

    /*
    Roatates the matrix
    */
    void LinSys::jacobi_rotate( int n ) {

        double s, c;

        if ( A(p,q) != 0.0 ) {

            double t, tau;
            tau = (A(p, q) - A(p,p))/(2*A(p,q));

            if ( tau >= 0 ) {

                t = 1.0/( tau + sqrt( 1.0 + tau*tau ) );

            } else {

                t = -1.0/( -tau + sqrt( 1.0 + tau*tau ) );

            }

            //cout << t << endl;

            c = 1/sqrt( 1 + t*t );
            s = c*t;

        } else {

            c = 1.0;
            s = 0.0;
        }

        
        double a_pp, a_qq, a_ip, a_iq, r_ip, r_iq;

        a_pp = A(p,p);
        a_qq = A(q,q);

        A(p,p) = c*c*a_pp - 2.0*c*s*A(p,q) + s*s*a_qq;
        A(q,q) = s*s*a_pp + 2.0*c*s*A(p,q) + c*c*a_qq;

        A(p,q) = 0.0;
        A(q,p) = 0.0;

        for ( int i = 0; i < n; i++ ) {

            if ( ( i != p ) && ( i != q ) ) {

                a_ip = A(i, p);
                a_iq = A(i, q);

                A(i,p) = c*a_ip - s*a_iq;
                A(p,i) = A(i,p);

                A(i,q) = c*a_iq + s*a_ip;
                A(q,i) = A(i,q);
            }

            r_ip = R(i,p);
            r_iq = R(i,q);

            R(i,p) = c*r_ip - s*r_iq;
            R(i,q) = c*r_iq + s*r_ip;
        }
    }

    /*
    Completes the Jacobi method. Runs offdiag() and jacobi_rotate()
    until the biggest non-diagonal number is lower than the tolerance.
    */
    void LinSys::iterations(int n) {

        while ( ( maxnondiag > tol ) && ( iter <= maxiter ) ) {
            
            offdiag(n);
            jacobi_rotate(n);
            iter++;
        }
    }

    // Prints the matrix A
    void LinSys::print_matrix() {

        cout << A << endl;

    }


    double LinSys::get_maxnondiag() {
        return maxnondiag;
    }

    void LinSys::extract_eigenvalues() {

        for (int i = 0; i < N; i++) {
            eig[i] = A(i,i);
        }
    }

    void LinSys::print_eigenvalues() {

        for (auto e: eig) {
            cout << e << endl;
        }
    }

    void write_eig_to_file(string filename) {

    }