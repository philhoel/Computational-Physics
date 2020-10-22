#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>


#include "solarsystem.hpp"


using namespace std;
using namespace arma;

/*
##########################################################
##########################################################

SolarSystem class

SolarSystem()
addPlanet()
setR_i()
setR_j()
force_function()
verlet()
euler()
writeValuesToFile()
writePlotInfo()

Planet class

getMass()
getName()
getID()



##########################################################
##########################################################
*/

SolarSystem::SolarSystem(int N, int size) {
    n = N;
    size = 0;
    h = 1./n;
    G = 4*PI*PI;
    r_i = zeros<vec> (2);
    r_j = zeros<vec> (2);
}

double SolarSystem::getPI() {
    return PI;
}

void SolarSystem::addPlanet(string name, int id, vec initial) {
    Planet new_obj(name, id, n);
    new_obj.addInitialValues(initial(0), initial(1), initial(2), initial(3));
    planetsArray.push_back(new_obj);
    size++;
}

void SolarSystem::setR_i(double x, double y) {
    r_i(0) = x;
    r_i(1) = y;
}

void SolarSystem::setR_j(double x, double y) {
    r_j(0) = x;
    r_j(1) = y;
}


double SolarSystem::force_function(int j, int i, int x) {
    
    vec sum = 0;
    for (int k = 0; k < n; k++) {
        if (k != j) {
            setR_j(planetsArray[j].pos(0,i), planetsArray[j].pos(0,i));
            sum += ((-G*planetsArray[k].getMass())/pow(abs(r_i - r_j), 2))*(r_i - r_j);
        }
    }

    return sum[x];
}

void SolarSystem::verlet() {

}

void SolarSystem::euler() {

    // i = time
    for (int i = 0; i < n; i++) {
        // j = planets
        for (int j = 0; j < size; j++) {

            setR_i(planetsArray[j].pos(0,i), planetsArray[j].pos(0,i));

            // Acceleration
            planetsArray[j].acc(0,i+1) = force_function(j, i, 0);
            planetsArray[j].acc(1,i+1) = force_function(j, i, 1);

            // Velocity
            planetsArray[j].vel(0,i+1) = planetsArray[j].vel(0,i) + planetsArray[j].acc(0,i)*h;
            planetsArray[j].vel(1,i+1) = planetsArray[j].vel(1,i) + planetsArray[j].acc(1,i)*h;

            // Posisition
            cout << planetsArray[j].pos(0,i) << endl;
            planetsArray[j].pos(0,i+1) = planetsArray[j].pos(0,i) + planetsArray[j].vel(0,i)*h;
            planetsArray[j].pos(1,i+1) = planetsArray[j].pos(1,i) + planetsArray[j].vel(1,i)*h;
        }
    }

}

void SolarSystem::writeValuesToFile(string filename) {
    ofstream my_file;
    my_file.open(filename);
    for (int i = 0; i < size; i++) {

        my_file << "-" << endl;

        for (int j = 0; j < n; j++) {
            cout << planetsArray[i].pos(0,j) << " " << planetsArray[i].pos(1,j) << endl;
            my_file << planetsArray[i].pos(0,j) << " " << planetsArray[i].pos(1,j);
            my_file << "    ";
            my_file << planetsArray[i].vel(0,j) << " " << planetsArray[i].vel(1,j);
            my_file << "    ";
            my_file << planetsArray[i].acc(0,j) << " " << planetsArray[i].acc(1,j) << endl;
        }
    }

    my_file.close();

}

void SolarSystem::writePlotInfo(string filename) {

    ofstream my_file;
    my_file.open(filename);
    my_file << n << endl;
    my_file << h << endl;
    for (int i = 0; i < size; i++) {
        my_file << planetsArray[i].getID() << " " << planetsArray[i].getName() << endl;
    }

    my_file.close();

}

// ---------------------------- PLANET class -----------------------------------

Planet::Planet(string Name, int id, int N) {
    name = Name;
    ID = id;
    n = N;
    pos = mat(2, n).fill(0.);
    vel = mat(2, n).fill(0.);
    acc = mat(2, n).fill(0.);
}

void Planet::addInitialValues(double x, double y, double vx, double vy) {
    pos(0,0) = x;
    pos(1,0) = y;
    vel(0,0) = vx;
    vel(1,0) = vy;
}

double Planet::getMass() {
    return mass;
}

string Planet::getName() {
    return name;
}

int Planet::getID() {
    return ID;
}