#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Planet {

    private:

        // Iterations
        int n;

        // ID - Planets number from the sun
        int ID;

        // Step size
        double h;

        // Name of planet
        string name;

        // Mass of planet
        double mass;

        // Gravitational force on planet
        double force;

        // Length form the sun
        double r;
        

    public:

        mat pos;
        mat vel;
        mat acc;

        Planet(string Name, int N);
        
        void update_r(int i);

        double getForce();

        void setForce(double F);

        string getName();

        int getID();

};