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

        double dt, dx, alpha;

        mat u;

        mat u_a;

        vec A;

        vec x;

        Solver(int N, int T, double DT);

        void AnalyticExpression();

        void ForwardStep(int t);

        void Tridiag(int t);

        void ForwardEuler();

        void BackwardEuler();

        void CrankNicholson();

        void WriteToFile(string Filename);

        void WriteToFile(string Filename, bool analytic);
};