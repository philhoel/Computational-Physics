#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <armadillo>

#include "Solver.hpp"

using namespace std;
using namespace arma;

Solver::Solver(int N, int T, double DT) {

    n = N;
    time = T;
    dt = DT;

    u = zeros<mat>(n+2, time);
    vec x = linspace(0,1,n+2);
    dx = x(1) - x(0);

    alpha = dt/pow(dx,2);


    for (int i = 1; i < n; i++) {
        u(i,0) = 0;
    }
    
}
/*
Solver::Solver(int N, int T, double DT, vec B, vec A, vec V) {

    n = N;
    time = T;
    dt = DT;

    b = B;
    a = A;
    u = zeros<mat>(n,time);
    
    for (int i = 1; i < n; i++) {
        u(i,0) = V(i);
    }

}
*/

double Solver::g(double x) {
    return sin(PI*x);
}

void Solver::ForwardStep(int t) {
    for (int x = 1; x < n; x++) {
        u(x,t) = alpha*u(x-1, t-1) + (1. - 2*alpha)*u(x, t-1) + alpha*u(x+1, t-1);
    }
}

void Solver::Tridiag(int t) {

    vec b;
    vec a;

    b = zeros<vec>(n);
    a = zeros<vec>(n);

    for (int x = 0; x < n; x++) {
        b(x) = 1+2*alpha;
        a(x) = -alpha;
    }

    for (int x = 1; x < n; x++) {

        a(x-1) /= b(x-1);
        u(x,t) /= b(x-1);
        b(x-1) = 1.;

        u(x+1,t) += u(x,t)*alpha;
        b(x) += a(x-1)*alpha;
    }

 
    u(n,t) /= b(n-1);
    b(n-1) = 1.;

    for (int x = n; x > 1; x--) {
        u(x-1,t) -= u(x,t)*a(x-2);
    }
    
    
   /*
    
    
    // Forward substitution
            for (int x = 1; x < n-1; x++) {
                //cout << "u" << u(x,t-1) << endl;
                b(x) = b(x) - (a(x)*a(x-1)/b(x-1));
                u(x,t-1) = u(x,t-1) - (a(x-1)*u(x-1,t-1)/b(x-1));
            }

            // Backward substitution
            cout << u(n-1,t) << endl;
            u(n-1,t) = u(n-1,t-1)/b(n-1);
            //cout << u(1,t) << endl;
            for (int x = n-2; x > 0; x--) {
                u(x,t) = (u(x,t-1) - a(x)*u(x+1,t))/b(x);
                cout << u(x,t) << endl;
            }

    */

}

void Solver::ForwardEuler() {

    for (int t = 1; t < time; t++) {
        u(0,t) = 0.0;
        u(n,t) = 1.0;
        ForwardStep(t);
    }
}

void Solver::BackwardEuler() {

    for (int t = 1; t < time-1; t++) {
        for (int x = 0; x < n+1; x++) {
            u(x,t) = u(x,t-1);
        }
        u(0,t) = 0;
        u(n,t) = 1;
        Tridiag(t);
    }

    u *= alpha;
}

void Solver::CrankNicholson() {

    alpha = alpha/2;

    for (int t = 1; t < time-1; t++) {
        u(0,t) = 0;
        u(n,t) = 1;
        ForwardStep(t);
        Tridiag(t);
    }

    u *= alpha;

}

void Solver::WriteToFile(string Filename) {

    ofstream myFile;
    myFile.open(Filename);
    for (int x = 0; x < n; x++) {
        for (int t = 0; t < time-1; t++) {
            myFile << u(x,t);
            myFile << ",";
        }

        myFile << u(x,time-1);
        myFile << endl;
    }

}