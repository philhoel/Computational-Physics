#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "armadillo"
#include "time.h"

using namespace std;
using namespace arma;

/*
    [b1 c1 0 0 ...] [x1]     [q1]
    [a1 b2 c2 0 ..] [x2]  =  [q2]
    [0 a2 b3 c3 ..] [x3]     [q3]
*/



class LinSys {

    private:

        /*
        Right hand side of equation
        */
        double f(double z) {
            return 100*exp(-10*z);
        }

        /*
        The analytic function
        */
        double analytic_f(double z) {
            return 1 - (1 - exp(-10))*z - exp(-10*z);
        }

    public:

        // Initializing vectors
        double h;
        double hh;
        vec x;
        int n;

        vec b;
        vec a;
        vec c;
        vec y;
        vec q;

        vec u;

        // LinSys contructor
        LinSys(int N) {

            n = N;
            h = 1./(n+1);
            hh = pow(h, 2);
            x = linspace(h, 1 - h, n);
            b = zeros<vec>(n, 1);
            a = zeros<vec>(n, 1);
            c = zeros<vec>(n, 1);
            y = zeros<vec>(n, 1);
            q = zeros<vec>(n, 1);

            u = zeros<vec>(n, 1);

            // Puts in values for tridiagonal matrix
            for (int i = 0; i < n; i++) {
            b[i] = 2;
            a[i] = -1;
            c[i] = -1;

            q[i] = hh*f(x[i]);


            u[i] = analytic_f(x[i]);
            
            }
        }

        // Resets values back to normal tridiagonal matrix
        void reset() {
            for (int i = 0; i < n; i++) {
            b[i] = 2;
            a[i] = -1;
            c[i] = -1;

            q[i] = hh*f(x[i]);

            y[i] = 0;
            }
        }


        void general_algorithm() {

            // Forward substitution
            for (int i = 1; i < n; i++) {
                b[i] = b[i] - (a[i-1]/b[i-1])*c[i-1];
                q[i] = q[i] - (a[i-1]/b[i-1])*q[i-1];


            }

            // Backward substitution
            y[n-1] = q[n-1]/b[n-1];
            for (int j = n-2; j >= 0; j--) {
                y[j] = (q[j] - c[j]*y[j+1])/b[j];
            }
        }

        void special_algorithm() {
        
            // Special Forward
            for (int k = 1; k < n; k++){
                q[k] = q[k] + ((k - 1.)/k)*q[k-1];
            }

            // Special Backward
            y[n-1] = q[n-1]/(n+1/n);
            for (int i = n-2; i >= 0; i--) {
                y[i] = (q[i] + y[i+1]*i/(i + 1));
            }
        }

        // Add vector to store values
        // Separate function into two functions
        // One for calulating and one for writing to file
        void error_analysis() {

            double epsilon;
            double max = 0;
            for (int i = 0; i < n; i++) {
                epsilon = abs((y[i] - u[i])/u[i]);
                if (epsilon > max) {
                    max = epsilon;
                }
            }

            epsilon = log10(max);

            cout << epsilon << endl;

            ofstream error_file;
            error_file.open("Error_analysis.txt");
            error_file << "n = ";
            error_file << n;
            error_file << " : epsi = ";
            error_file << epsilon << "\n";

            error_file.close();
        }

        void write_to_file(string filename) {
            ofstream my_file;
            my_file.open(filename);
            my_file << n << "\n";
            for (int i = 0; i < n; i++) {
                my_file << y[i] << "\n";
            }

            //my_file << "END\n";

            my_file.close();
        }

        void write_analytic(string filename) {
            ofstream my_file;
            my_file.open(filename);
            my_file << n << "\n";
            for (int i = 0; i < n; i++) {
                my_file << u[i] << "\n";
            }

            //my_file << "END\n";

            my_file.close();
        }

        void LU_decomp() {

            mat A = zeros<mat>(n, n);
            mat L, U, P;

            lu(L,U,P,A);
        }


};



int main() {

    clock_t start, finish;

    LinSys LS10(10);
    LinSys LS1k(1000);
    LinSys LS1M(1000000);

    LS10.general_algorithm();
    LS10.write_to_file("general_10.txt");
    LS10.error_analysis();

    LS10.reset();
    LS10.special_algorithm();
    LS10.write_to_file("special_10.txt");

    LS10.write_analytic("analytic_10.txt");

    LS1k.general_algorithm();
    LS1k.write_to_file("general_1k.txt");
    LS1k.error_analysis();
    
    LS1k.reset();
    LS1k.special_algorithm();
    LS1k.write_to_file("special_1k.txt");

    LS1k.write_analytic("analytic_1k.txt");

    LS1M.general_algorithm();
    LS1M.write_to_file("general_1M.txt");
    LS1M.error_analysis();

    LS1M.reset();
    LS1M.special_algorithm();
    LS1M.write_to_file("special_1M.txt");
    
    LS1M.write_analytic("analytic_1M.txt");

    return 0;
}