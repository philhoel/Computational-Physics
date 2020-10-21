#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>


class SolarSystem {

    private:

        const double PI = 3.141592653589793238463;

        int n;
        double solarMass;
        double solarRadius;
        double G;

        //List of planets
        Planets[] planetsArray;
        //List of positions
        //List of velocities
        //List of acceleration

    public:

        SolarSystem(int N);

        void force_function(int i);

        void verlet();

        void euler();

        void writeValuesToFile();

        void writePlotInfo();
};