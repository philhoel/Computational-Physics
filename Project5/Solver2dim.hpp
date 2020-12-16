#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <armadillo>

using namespace std;
using namespace arma;

class Solver {

    public:

        const double PI = 3.141592653589793;

        int n, time; // Iteration points

        double dt, h, hh, alpha;

        mat u;

        Solver(int N, int T, double DT);

        double g(double x);

        void ForwardStep(int t);

        void Tridiag(int t);

        void CrankNicholson();

        void WriteToFile(string Filename);
};