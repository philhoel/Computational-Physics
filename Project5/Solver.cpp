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
    t_steps = linspace(0,1,T);
    dt = DT;

    u = zeros<mat>(n+2, time);
    u_a = zeros<mat>(n+2, time);
    //u_a = zeros<vec>(n+2);
    A = zeros<vec>(n+2);
    x = linspace(0,1,n+2);
    dx = x(1) - x(0);

    alpha = dt/pow(dx,2);


    for (int i = 1; i < n; i++) {
        u(i,0) = 0;
    }

    //cout << exp(-4.45e2) << endl;
    
}

void Solver::AnalyticExpression() {

    double sum = 0;
    for (int i = 1; i < n+1; i++) {
        A(i) = (2*(PI*i*cos(PI*i) - sin(PI*i)))/(PI*PI*i*i);
        //cout << A(i) << endl;
    }
    
    for (int t = 1; t < time; t++) {
        for (int j = 1; j < n+1; j++) {
            for (int i = 1; i < n+1; i++) {
                sum += A(i)*exp(-pow(PI*i,2)*t_steps(t))*sin(i*PI*x(j));
                //cout << exp(-pow(PI*i,2)*t) << endl;
            }

            u_a(j,t) = x(j) + sum;
            sum = 0;
        }
    }
    

   //double t = 0.1;

   /*

    for (int j = 1; j < n+1; j++) {
            for (int i = 1; i < n+1; i++) {
                sum += A(i)*exp(-pow(PI*i,2)*t)*sin(i*PI*x(j));
                cout << exp(-pow(PI*i,2)*t) << endl;
            }

            u_a(j) = x(j) + sum;
            sum = 0;

    */
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

    myFile.close();

}

void Solver::WriteToFile(string Filename, bool analytic) {

    ofstream myFile;
    myFile.open(Filename);
    for (int x = 0; x < n; x++) {
        for (int t = 0; t < time-1; t++) {
            myFile << u_a(x,t);
            myFile << ",";
        }

        myFile << u(x,time-1);
        myFile << endl;
    }

    myFile.close();
}