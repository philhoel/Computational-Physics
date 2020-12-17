#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <armadillo>

using namespace std;
using namespace arma;

class Solver2dim {

    public:

        const double PI = 3.141592653589793;

        int n, time; // Iteration points

        double dt, h, hh, alpha, dx;

        mat u, v;

        mat temp;
        mat w;

        vector<mat> values;

        Solver2dim(int N, int T, double DT);

        void ForwardStep();

        void ForwardEuler(int t1, int t2, int t3, int t4);

        void WriteToFile(string Filename, int k);

        void WriteToMultipleFiles(string file1, string file2, string file3, string file4);
};