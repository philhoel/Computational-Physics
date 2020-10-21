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
    h = 1/n;
    G = 4*PI*PI;
    planetsArray = new Planets[n];
}


SolarSystem::force_function(int i) {
    
    double sum = 0;
    for (int k = 0; k < n; k++) {
        
    }
}

SolarSystem::verlet() {

}

SolarSystem::euler() {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            planetsArray[i].update_r(j);

            // Acceleration
            planetsArray[i].acc(0,j+1) = force_function(i);
            planetsArray[i].acc(1,j+1) = force_function(i);

            // Velocity
            planetsArray[i].vel(0,j+1) = planetsArray[i].vel(0,j) + planetsArray[i].acc(0,j)*h;
            planetsArray[i].vel(1,j+1) = planetsArray[i].vel(1,j) + planetsArray[i].acc(1,j)*h;

            // Posisition
            planetsArray[i].pos(0,j+1) = planetsArray[i].pos(0,j) + planetsArray[i].vel(0,j)*h;
            planetsArray[i].pos(1,j+1) = planetsArray[i].pos(1,j) + planetsArray[i].vel(1,j)*h;
        }
    }

}

SolarSystem::writeValuesToFile() {

}

SolarSystem::writePlotInfo() {

}