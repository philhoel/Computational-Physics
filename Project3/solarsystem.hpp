#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <vector>


using namespace std;
using namespace arma;

// ------------------------ Planet Class -----------------------------

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

        vec kin;
        vec pot;

        mat p;
        mat L;

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
        double T;
        double G;
        double h;
        int size;

        vector<Planet> planetsArray;
        vec r_i = zeros<vec> (2);
        vec r_j = zeros<vec> (2);

    public:

        SolarSystem(int N, double Time);

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