#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
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

Planet()
addInitialValues()
getMass()
getName()
getID()



##########################################################
##########################################################
*/




SolarSystem::SolarSystem(int N, double Time) {
    n = N;
    T = Time;
    size = 0;
    count = 0;
    h = T*(1./(n-1));
    G = 4*PI*PI;
    r_i = zeros<vec> (2);
    r_j = zeros<vec> (2);
}

void SolarSystem::massCenter()
{
    double tot_mass = 0;
    double tmp_mass;
    vec R_M = zeros<vec>(2);
    vec V_M = zeros<vec>(2);
    for(int i = 0; i < size; i++)
    {   
        tmp_mass = planetsArray[i].getMass();
        
        R_M[0] += planetsArray[i].pos(0,count)*tmp_mass;
        R_M[1] += planetsArray[i].pos(1,count)*tmp_mass;

        tot_mass += tmp_mass;

        V_M[0] += planetsArray[i].vel(0,count)*tmp_mass;
        V_M[1] += planetsArray[i].vel(1,count)*tmp_mass;

    }

    R_M = R_M/tot_mass;
    V_M = V_M/tot_mass;

    for(int i = 0; i < size; i++)
    {
        planetsArray[i].pos(0,count) = planetsArray[i].pos(0,count) - R_M[0];
        planetsArray[i].pos(1,count) = planetsArray[i].pos(1,count) - R_M[1];

        planetsArray[i].vel(0,count) = planetsArray[i].vel(0,count) - V_M[0];
        planetsArray[i].vel(1,count) = planetsArray[i].vel(1,count) - V_M[1];

    }
}

double SolarSystem::getPI() {
    return PI;
}



// Adds planet to solar system
// Starts by calling addInitialValues() to add start values for planet
// then adds planet to planetsArray
void SolarSystem::addPlanet(string name, int id, vec initial, double mass) {

    Planet new_obj(name, id, n, mass);

    new_obj.addInitialValues(initial(0), initial(1), initial(2), initial(3));

    planetsArray.push_back(new_obj);

    size++;
}



// Sets r of current planet
void SolarSystem::setR_i(double x, double y) {
    r_i(0) = x;
    r_i(1) = y;
}



// Sets r of planets pulling on current planet
void SolarSystem::setR_j(double x, double y) {
    r_j(0) = x;
    r_j(1) = y;
}



/*
Calculates the force of the current planet

Parameter:
    j - Current planet
    i - Current time step
    x - To choose between x or y value

First if statement is condition for when there is only one planet
*/
double SolarSystem::force_function(int j, int i, int x) {
    
    vec sum = zeros<vec> (2);
    double zum_x = 0;
    double zum_y = 0;


    for (int k = 0; k < size; k++) {

        if (size == 1) {

            //cout << "hei" << endl;
            double r_ii = sqrt(pow(r_i[0], 2) + pow(r_i[1], 2));
            zum_x += ((-G*planetsArray[k].getMass())/pow(r_ii, 3))*planetsArray[j].pos(0,i);
            zum_y += ((-G*planetsArray[k].getMass())/pow(r_ii, 3))*planetsArray[j].pos(1,i);
            //cout << r_ii << endl;

        } else if (k != j) {

            setR_j(planetsArray[k].pos(0,i), planetsArray[k].pos(1,i));
            double r_ii = sqrt(pow(r_i[0] - r_j[0], 2) + pow(r_i[1] - r_j[1], 2));
            sum += ((-G*planetsArray[k].getMass())/pow(r_ii, 2))*(r_i - r_j);
        }
    }

    if (size == 1) {
        sum[0] = zum_x;
        sum[1] = zum_y;
    }

    return sum[x];
}



// Verlet Method
void SolarSystem::verlet() {

    // time
    for (int i = 0; i < n-1; i++) {
        // planets
        for (int j = 0; j < size; j++) {

            setR_i(planetsArray[j].pos(0,i), planetsArray[j].pos(1,i));

            // Position
            planetsArray[j].pos(0,i+1) = planetsArray[j].pos(0,i) + planetsArray[j].vel(0,i)*h + pow(h,2)*0.5*planetsArray[j].acc(0,i);
            planetsArray[j].pos(1,i+1) = planetsArray[j].pos(1,i) + planetsArray[j].vel(1,i)*h + pow(h,2)*0.5*planetsArray[j].acc(1,i);

            // Acceleration
            planetsArray[j].acc(0,i+1) = force_function(j, i+1, 0)/planetsArray[j].getMass();
            planetsArray[j].acc(1,i+1) = force_function(j, i+1, 1)/planetsArray[j].getMass();

            // Velocity
            planetsArray[j].vel(0,i+1) = planetsArray[j].vel(0,i) + h*(planetsArray[j].acc(0,i) + planetsArray[j].acc(0,i+1))/2;
            planetsArray[j].vel(1,i+1) = planetsArray[j].vel(1,i) + h*(planetsArray[j].acc(1,i) + planetsArray[j].acc(1,i+1))/2;
        }
    }

}



// Euler Method
void SolarSystem::euler() {

    massCenter();
    count += 1;

    // i = time
    for (int i = 0; i < n-1; i++) {
        // j = planets
        for (int j = 0; j < size; j++) {

            //cout << planetsArray[j].pos(0,i) << " " << planetsArray[j].pos(1,i) << endl;

            setR_i(planetsArray[j].pos(0,i), planetsArray[j].pos(1,i));

            // Acceleration
            planetsArray[j].acc(0,i) = force_function(j, i, 0);
            planetsArray[j].acc(1,i) = force_function(j, i, 1);

            // Velocity
            planetsArray[j].vel(0,i+1) = planetsArray[j].vel(0,i) + planetsArray[j].acc(0,i)*h;
            planetsArray[j].vel(1,i+1) = planetsArray[j].vel(1,i) + planetsArray[j].acc(1,i)*h;

            // Posisition
            //cout << planetsArray[j].pos(0,i) << endl;
            planetsArray[j].pos(0,i+1) = planetsArray[j].pos(0,i) + planetsArray[j].vel(0,i)*h;
            planetsArray[j].pos(1,i+1) = planetsArray[j].pos(1,i) + planetsArray[j].vel(1,i)*h;
        }
    }

}



// Write the values of position, velocity and acceleration to a .txt file
void SolarSystem::writeValuesToFile(string filename) {

    ofstream my_file;
    my_file.open(filename);
    char a = 45;

    for (int i = 0; i < size; i++) {

        my_file << a << endl;

        for (int j = 0; j < n-1; j++) {
            my_file << planetsArray[i].pos(0,j) << " " << planetsArray[i].pos(1,j);
            //cout << planetsArray[i].pos(0,j) << " " << planetsArray[i].pos(1,j);
            my_file << " ";
            //cout << " ";
            my_file << planetsArray[i].vel(0,j) << " " << planetsArray[i].vel(1,j);
            //cout << planetsArray[i].vel(0,j) << " " << planetsArray[i].vel(1,j);
            my_file << " ";
            //cout << " ";
            my_file << planetsArray[i].acc(0,j) << " " << planetsArray[i].acc(1,j) << endl;
            //cout << planetsArray[i].acc(0,j) << " " << planetsArray[i].acc(1,j) << endl;
        }
    }

    my_file.close();

}



// Write additional information of planets to a seperate file
// This includes n, h, name and ID
void SolarSystem::writePlotInfo(string filename) {

    char a = 45;

    ofstream my_file;
    my_file.open(filename);
    my_file << n << endl;
    my_file << h << endl;

    for (int i = 0; i < size; i++) {

        my_file << planetsArray[i].getID() << endl;
        my_file << planetsArray[i].getName() << endl;
        my_file << a << endl;
    }

    my_file.close();

}



//                                                                               //
// ---------------------------- PLANET class ----------------------------------- //
//                                                                               //

Planet::Planet(string Name, int id, int N, double Mass) {
    name = Name;
    ID = id;
    n = N;
    mass = Mass;
    pos = mat(2, n).fill(0.);
    vel = mat(2, n).fill(0.);
    acc = mat(2, n).fill(0.);

    // Kinetic and potetial energy
    kin = zeros<vec> (n);
    pot = zeros<vec> (n);

    // Momentum and angular momentum
    // L = r x p
    p = mat(2, n).fill(0.);
    L = mat(2, n).fill(0.);
}



// Adds initial values to position and velocity
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