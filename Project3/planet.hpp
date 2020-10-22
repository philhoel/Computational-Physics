#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Planet {

    private:

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

        Planet(string Name, int id);

        double getMass();

        string getName();

        int getID();

};