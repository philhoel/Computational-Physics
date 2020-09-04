#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include "armadillo"
#include "time.h"

using namespace std;
using namespace arma;

/*
    [b1 c1 0 0 ...] [x1]     [q1]
    [a1 b2 c2 0 ..] [x2]  =  [q2]
    [0 a2 b3 c3 ..] [x3]     [q3]
*/

struct LinSys {
    vec b;
    vec a;
    vec c;
    vec y;
    vec q;

    LinSys(int n) {
        b = zeros<vec>(n, 1);
        a = zeros<vec>(n, 1);
        c = zeros<vec>(n, 1);
        y = zeros<vec>(n, 1);
        q = zeros<vec>(n, 1);
    }

};

double f(double x) {
    return 100*exp(-10*x);
}

LinSys setup(int n) {

   double h = 1/(n-2);
   vec x = linspace(h, 1 - h, n);

   LinSys LS(n);

    for (int i = 0; i < n; i++) {
        LS.b[i] = 2;
        LS.a[i] = -1;
        LS.c[i] = -1;

        LS.q[i] = f(x[i]);
    }


    return LS;
}

void write_to_file(string filename, vec y, int n) {

    ofstream my_file;
    my_file.open(filename);
    my_file << n << "\n";
    for (int i = 0; i < n; i++) {
        my_file << y[i] << "\n";
    }

    my_file.close();
}

void general_calculation(int n, string filename) {

    LinSys LS(n);
    LS = setup(n);

    // Forward substitution
    for (int i = 1; i < n; i++) {
        LS.b[i] = LS.b[i] - (LS.a[i-1]/LS.b[i-1])*LS.c[i-1];
        LS.q[i] = LS.q[i] - (LS.a[i-1]/LS.b[i-1])*LS.q[i-1];
    }

    // Backward substitution
    LS.y[n-1] = LS.q[n-1]/LS.b[n-1];
    for (int j = n-2; j >= 0; j--) {
        LS.y[j] = (LS.q[j] - LS.c[j]*LS.y[j+1])/LS.b[j];
    }

    write_to_file(filename, LS.y, n);

}

void special_calculation(int n, string filename) {

    LinSys LS(n);
    LS = setup(n);

    // Special Forward
    for (int k = 1; k < n; k++){
        LS.q[k] = LS.q[k] + ((k - 1.)/k)*LS.q[k-1];
    }

    // Special Backward
    LS.y[n-1] = LS.q[n-1]/(n+1/n);
    for (int i = n-2; i >= 0; i--) {
        LS.y[i] = (LS.q[i] + LS.y[i+1]*i/(i + 1));
    }


    write_to_file(filename, LS.y, n);

}

double error_analysis(int n) {

    LinSys LS(n);
    LS = setup(n);

    // Forward substitution
    for (int i = 1; i < n; i++) {
        LS.b[i] = LS.b[i] - (LS.a[i-1]/LS.b[i-1])*LS.c[i-1];
        LS.q[i] = LS.q[i] - (LS.a[i-1]/LS.b[i-1])*LS.q[i-1];
    }

    // Backward substitution
    LS.y[n-1] = LS.q[n-1]/LS.b[n-1];
    for (int j = n-2; j >= 0; j--) {
        LS.y[j] = (LS.q[j] - LS.c[j]*LS.y[j+1])/LS.b[j];
    }

    double epsilon;
    double eps_temp;
    double max = 0;
    for (int i = 0; i < n; i++) {
        eps_temp = abs((LS.y[i] - LS.q[i])/LS.q[i]);
        if (eps_temp > max) {
            max = eps_temp;
        }
    }

    epsilon = log10(max);

    return epsilon;

}


int main(int argc, char *argv[]) {

    //general_calculation(10, "general_10.txt");
    //general_calculation(1000, "general_1k.txt");
    //general_calculation(1000000, "general_1M.txt");

    //special_calculation(10, "special_10.txt");
    //special_calculation(1000, "special_1k.txt");
    //special_calculation(1000000, "special_1M.txt");

    cout << error_analysis(10) << endl;
    cout << error_analysis(100) << endl;
    cout << error_analysis(1000) << endl;
    cout << error_analysis(10000) << endl;
    cout << error_analysis(100000) << endl;
    cout << error_analysis(1000000) << endl;
    

    return 0;
}