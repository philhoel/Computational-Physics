#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include "solarsystem.hpp"
#include "planet.hpp"

using namespace std;
using namespace arma;

/*
##########################################################
##########################################################

SolarSystem class

##########################################################
##########################################################
*/

SolarSystem::SolarSystem(int N) {
    n = N;
    size = 0;
    h = 1/n;
    G = 4*PI*PI;
    planetsArray = new Planets[size];
    r_i = zeros<vec> (1, 2);
    r_j = zeros<vec> (1, 2);
}

SolarSystem::setR_i(double x, double y) {
    r_i(0,0) = x;
    r_i(0,1) = y;
}

SolarSystem::setR_j(double x, double y) {
    r_j(0,0) = x;
    r_j(0,1) = y;
}


SolarSystem::force_function(int j, int i) {
    
    double sum = 0;
    for (int k = 0; k < n; k++) {
        if (k != j) {
            setR_j(planetsArray[j].pos(0,i), planetsArray[j].pos(0,i));
            sum += ((-G*planetsArray[k].getMass())/pow(abs(r_i - r_j)), 2))*(r_i - r_j) //(r - r)
        }    
    }
}

SolarSystem::verlet() {

}

SolarSystem::euler() {

    // i = time
    for (int i = 0; i < n; i++) {
        // j = planets
        for (int j = 0; j < size; j++) {

            setR_i(planetsArray[j].pos(0,i), planetsArray[j].pos(0,i));

            force_function(i);

            // Acceleration
            planetsArray[j].acc(0,i+1) = planetsArray[j].getForce();
            planetsArray[j].acc(1,i+1) = planetsArray[j].getForce();

            // Velocity
            planetsArray[j].vel(0,i+1) = planetsArray[j].vel(0,i) + planetsArray[j].acc(0,i)*h;
            planetsArray[j].vel(1,i+1) = planetsArray[j].vel(1,i) + planetsArray[j].acc(1,i)*h;

            // Posisition
            planetsArray[j].pos(0,i+1) = planetsArray[j].pos(0,i) + planetsArray[j].vel(0,i)*h;
            planetsArray[j].pos(1,i+1) = planetsArray[j].pos(1,i) + planetsArray[j].vel(1,i)*h;
        }
    }

}

SolarSystem::writeValuesToFile(string filename) {
    ofstream my_file;
    my_file.open(filename);
    for (int i = 0; i < size; i++) {

        my_file << "-" << endl;

        for (int j = 0; j < n; j++) {
            my_file << planetsArray[i].pos(0,j) << " " << planetsArray[i].pos(1,j);
            my_file << "    ";
            my_file << planetsArray[i].vel(0,j) << " " << planetsArray[i].vel(1,j);
            my_file << "    ";
            my_file << planetsArray[i].acc(0,j) << " " << planetsArray[i].acc(1,j) << endl;
        }
    }

    my_file.close();

}

SolarSystem::writePlotInfo() {

    ofstream my_file;
    my_file.open(filename);
    my_file << n << endl;
    my_file << h << endl;
    for (int i = 0; i < size; i++) {
        my_file << planetsArray[i].getID() << " " << planetsArray[i].getName() << endl;
    }

}