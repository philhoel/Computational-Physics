#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "armadillo"
#include "time.h"

using namespace std;
using namespace arma;


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


        double error_analysis() {

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

            return epsilon;
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


void error_to_file(vector<double> vec) {

        int x = 10;

        ofstream error_file;
        error_file.open("Error_analysis.txt");
        for (auto y : vec) {
            error_file << "n = ";
            error_file << x;
            error_file << " : Error = ";
            error_file << y << endl;
            x *= 10;
        }

        error_file.close();
    }


int main() {

    vector<double> epsi;

    clock_t start, finish;
    double LS10_LU;
    double LS10_general;

    LinSys LS10(10);
    LinSys LS100(100);
    LinSys LS1k(1000);
    LinSys LS10k(10000);
    LinSys LS100k(100000);
    LinSys LS1M(1000000);
    LinSys LS10M(10000000);

    start = clock();
    LS10.general_algorithm();
    finish = clock();
    LS10_general = (double)(finish - start)/(CLOCKS_PER_SEC);
    LS10.write_to_file("general_10.txt");
    epsi.push_back(LS10.error_analysis());

    LS10.reset();
    LS10.special_algorithm();
    LS10.write_to_file("special_10.txt");

    LS10.write_analytic("analytic_10.txt");

    LS100.general_algorithm();
    LS100.write_to_file("general_100.txt");
    epsi.push_back(LS100.error_analysis());
    
    LS100.reset();
    LS100.special_algorithm();
    LS100.write_to_file("special_100.txt");

    LS100.write_analytic("analytic_100.txt");

    LS1k.general_algorithm();
    LS1k.write_to_file("general_1k.txt");
    epsi.push_back(LS1k.error_analysis());
    
    LS1k.reset();
    LS1k.special_algorithm();
    LS1k.write_to_file("special_1k.txt");

    LS1k.write_analytic("analytic_1k.txt");

    LS10k.general_algorithm();
    LS10k.error_analysis();

    LS100k.general_algorithm();
    LS100k.error_analysis();

    LS1M.general_algorithm();
    epsi.push_back(LS1M.error_analysis());

    LS10M.general_algorithm();
    epsi.push_back(LS10M.error_analysis());

    error_to_file(epsi);

    start = clock();
    LS10.LU_decomp();
    finish = clock();
    LS10_LU = (double)(finish - start)/(CLOCKS_PER_SEC);


    cout << "runtime General algo for n = 10: " << LS10_general << endl;
    cout << "runtime LU for n = 10: " << LS10_LU << endl;

    return 0;
}