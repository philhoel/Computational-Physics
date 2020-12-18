#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <armadillo>

#include "Solver.hpp"
#include "Solver2dim.hpp"

using namespace std;
using namespace arma;

Solver2dim::Solver2dim(int N, int T, double DT) {

    n = N;
    time = T;
    dt = DT;

    u = zeros<mat>(n+2, n+2);
    v = zeros<mat>(n+2, n+2);
    temp = zeros<mat>(n+2, n+2);
    w = zeros<mat>(n+2, n+2);
    h = 1./(n+1);

    int z = 1;

    alpha = dt/pow(h,4);

    for (int x = 1; x < n+1; x++) {
        for (int y = n/2; y < n+1; y++) {
            v(x,y) = z;
        }
    }

}


void Solver2dim::ForwardStep() {

    for (int x = 1; x < n+1; x++) {
        for (int y = 1; y < n+1; y++) {
            u(x,y) = v(x,y) + alpha*(v(x+1,y) - 4*v(x,y) + v(x-1,y) + v(x,y+1) + v(x,y-1));

        }

    }


    for (int x = 1; x < n+1; x++) {
        for (int y = 1; y < n+1; y++) {
            temp(x,y) = u(x,y);
            u(x,y) = v(x,y);
            v(x,y) = temp(x,y);
        }
    }

}

void Solver2dim::ForwardEuler(int t1, int t2, int t3, int t4) {

    for (int i = 0; i < n+2; i++) {
        v(0,i) = 0;
        v(i,0) = 0;
        v(n+1,i) = 0;
        v(i,n+1) = 0;
    }

    for (int t = 1; t < time; t++) {
        ForwardStep();

        if ((t == t1) || (t == t2) || (t == t3) || (t == t4)) {
            w = v;
            values.push_back(w);
        }
    }

}



void Solver2dim::WriteToFile(string Filename, int k) {

    ofstream MyFile;
    MyFile.open(Filename);
    for (int x = 0; x < n+2; x++) {
        for (int y = 0; y < n+1; y++) {
            MyFile << values[k](x,y);
            MyFile << ",";
        }

        MyFile << values[k](x,n-1);
        MyFile << endl;
    }

    MyFile.close();
}

void Solver2dim::WriteToMultipleFiles(string file1, string file2, string file3, string file4) {

    WriteToFile(file1, 0);
    WriteToFile(file2, 1);
    WriteToFile(file3, 2);
    WriteToFile(file4, 3);
}