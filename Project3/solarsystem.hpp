#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <vector>


using namespace std;
using namespace arma;

// ------------------------ PLANET Class -----------------------------

class Planet {

    private:

        int n;

        // ID - Planets number from the sun
        int ID;

        // Name of planet
        string name;

        // Mass of planet
        double mass;
        

    public:

        mat pos;
        mat vel;
        mat acc;

        Planet(string Name, int id, int N, double Mass);

        void addInitialValues(double x, double y, double vx, double vy);

        double getMass();

        string getName();

        int getID();

};


class SolarSystem {

    private:

        const double PI = 3.141592653589793238463;

        int n;
        double G;
        double h;
        int size;

        vector<Planet> planetsArray;
        vec r_i;
        vec r_j;

    public:

        SolarSystem(int N);

        void addPlanet(string name, int id, vec initial, double mass);

        void setR_i(double x, double y);

        void setR_j(double x, double y);

        double force_function(int j, int i, int x);

        void verlet();

        void euler();

        void writeValuesToFile(string filename);

        void writePlotInfo(string filename);

        double getPI();
};