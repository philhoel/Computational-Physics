#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>


class SolarSystem {

    private:

        const double PI = 3.141592653589793238463;

        int n;
        double G;
        double h;

        Planets[] planetsArray;
        vec r_i;
        vec r_j;

    public:

        SolarSystem(int N);

        void setR_i(double x, double y);

        void setR_j(double x, double y);

        void force_function(int i);

        void verlet();

        void euler();

        void writeValuesToFile(string filename);

        void writePlotInfo();
};