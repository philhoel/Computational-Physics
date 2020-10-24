#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

// -------------------------------------------------------------------------------------//
// -------------------------------- CelestBody Struct --------------------------------- //
// -------------------------------------------------------------------------------------//

/*
Constructor - Takes in name, mass and number of iterations
*/
CelestBody::CelestBody(string Name, double Mass, int n) {

    name = Name;
    mass = Mass;

    pos = mat(3,n).fill(0.);
    vel = mat(3,n).fill(0.);
    acc = mat(3,n).fill(0.);

    kin = zeros<vec>(n);
    pot = zeros<vec>(n);

    p = mat(3,n).fill(0.);
    L = mat(3,n).fill(0.);
}

/*
initialValues()

Parameters:
    double x
    double y
    double z

    double vx
    double vy
    double vz
*/
void CelestBody::initialValues(double x, double y, double z, double vx, double vy, double vz) {
    pos(0, 0) = x;
    pos(1, 0) = y;
    pos(2, 0) = z;

    vel(0, 0) = vx;
    vel(1, 0) = vy;
    vel(2, 0) = vz;

}

/*
Overloaded
initialValues()

Parameters:
    double x
    double y
    double z
*/
void CelestBody::initialValues(double x, double y, double z) {
    pos(0, 0) = x;
    pos(1, 0) = y;
    pos(2, 0) = z;

}

// ---------------------------------------------------------------------------------------------------------- //
// ------------------------------------------- SolarSystem class -------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------- //

SolarSystem::SolarSystem(int N, double Time) {

    n = N;
    T = Time;
    h = T*(1./(n-1));

    g = 4*PI*PI;

    size = 0;
}

/*
addBody() - Adds a new celestial body to list

Parameters:
    name - name of body
    mass - mass of body (should be scaled for for solarmass)
    initial - vector with initial values (Takes 6 values)
*/
void SolarSystem::addBody(string name, double mass, vec initial) {
    CelestBody new_obj(name, mass, n);
    new_obj.initialValues(initial(0), initial(1), initial(2), initial(3), initial(4), initial(5));
    CB.push_back(new_obj);

    size++;
}

/*
addSun() - Adds a Sun to list (spescial method for sun)

Parameters:
    name - name of body
    mass - mass of body (should be scaled for for solarmass)
    initial - vector with initial values (initial values takes only 3 values)
*/
void SolarSystem::addSun(string name, double mass, vec initial) {
    CelestBody new_obj(name, mass, n);
    new_obj.initialValues(initial(0), initial(1), initial(2));
    CB.push_back(new_obj);

    size++;
}


/*
gravitation() - Calculates the gravitational force on a body from all other bodies in system

Parameters:
    SP - Step point (Takes in the current step point)
    cnt - Current number in body list
    r_vec_cnt - temporary positional values for current body (x, y, z)
    axis - A number from 0 - 2, to decide to return between x, y or z
*/
double SolarSystem::gravitation(int SP, int cnt, vec r_vec_cnt, int axis) {

    double F = 0;
    double r;
    double beta = 3;
    vec r_vec_body = zeros<vec>(3);

    for (int body = 0; body < size; body++) {
        if (body != cnt) {

            // createing temporary r vector for bodies around current body
            r_vec_body(0) = CB[body].pos(0,SP); r_vec_body(1) = CB[body].pos(1,SP); r_vec_body(2) = CB[body].pos(2,SP);

            // Creating r length -> sqrt(x^2 + y^2 + z^2)
            r = sqrt( pow(CB[cnt].pos(0,SP) - r_vec_body(0), 2) + pow(CB[cnt].pos(2,SP) - r_vec_body(1), 2) + pow(CB[cnt].pos(2,SP) - r_vec_body(2), 2) );

            // Calculating the sum of F
            F += ( ( -g * CB[cnt].mass * CB[body].mass ) * ( r_vec_cnt[axis] - r_vec_body[axis] ) / pow(r, beta) );
            
        }
    }

    cout << CB[cnt].name << " " << axis << ": " << F << endl;

    return F;

}

/*
massCenter() - Calculates the center of mass in the system.
               Loops over all bodies and divides their mass by the center of mass.
               Also does same for velocity
*/
void SolarSystem::massCenter() {

    double tot_mass = 0;
    double tmp_mass;

    vec r_c = zeros<vec>(3);
    vec v_c = zeros<vec>(3);

    for (int i = 0; i < size; i++) {

        tmp_mass = CB[i].mass;

        cout << tmp_mass << endl;

        r_c[0] += CB[i].pos(0,0)*tmp_mass;
        r_c[1] += CB[i].pos(1,0)*tmp_mass;
        r_c[2] += CB[i].pos(2,0)*tmp_mass;

        tot_mass += tmp_mass;

        v_c[0] += CB[i].vel(0,0)*tmp_mass;
        v_c[1] += CB[i].vel(1,0)*tmp_mass;
        v_c[2] += CB[i].vel(2,0)*tmp_mass;
    }

    r_c = r_c/tot_mass;
    v_c = v_c/tot_mass;

    for (int j = 0; j < size; j++) {

        CB[j].pos(0,0) -= r_c[0];
        CB[j].pos(1,0) -= r_c[1];
        CB[j].pos(2,0) -= r_c[2];

        CB[j].vel(0,0) -= v_c[0];
        CB[j].vel(1,0) -= v_c[1];
        CB[j].vel(2,0) -= v_c[2];

    }

}

/*
verlet() - The numerical algorithm "Velocity Verlet"
           Calculates values for next time step
*/
void SolarSystem::verlet() {

    vec r_vec_cnt = zeros<vec>(3);
    massCenter();

    // SP = Step Point (Time point)
    for (int SP = 0; SP < n-1; SP++) {

        // cnt = current (for current body)
        for (int cnt = 0; cnt < size; cnt++) {

            //cout << CB[cnt].pos(0,SP) << endl;

            CB[cnt].pos(0, SP+1) = CB[cnt].pos(0, SP) + CB[cnt].vel(0, SP)*h + ( pow(h,2)*CB[cnt].acc(0, SP) ) / 2;
            CB[cnt].pos(1, SP+1) = CB[cnt].pos(1, SP) + CB[cnt].vel(1, SP)*h + ( pow(h,2)*CB[cnt].acc(1, SP) ) / 2;
            CB[cnt].pos(2, SP+1) = CB[cnt].pos(2, SP) + CB[cnt].vel(2, SP)*h + ( pow(h,2)*CB[cnt].acc(2, SP) ) / 2;

            // Creates a temporary r vector for the current body
            r_vec_cnt(0) = CB[cnt].pos(0,SP+1); r_vec_cnt(1) = CB[cnt].pos(1,SP+1); r_vec_cnt(2) = CB[cnt].pos(2,SP+1);

            //cout << r_vec_cnt << endl;

            CB[cnt].acc(0, SP+1) = gravitation(SP, cnt, r_vec_cnt, 0)/CB[cnt].mass;
            CB[cnt].acc(1, SP+1) = gravitation(SP, cnt, r_vec_cnt, 1)/CB[cnt].mass;
            CB[cnt].acc(2, SP+1) = gravitation(SP, cnt, r_vec_cnt, 2)/CB[cnt].mass;   

            CB[cnt].vel(0, SP+1) = CB[cnt].vel(0,SP) + h*( CB[cnt].acc(0,SP) + CB[cnt].acc(0,SP+1) ) / 2;
            CB[cnt].vel(1, SP+1) = CB[cnt].vel(1,SP) + h*( CB[cnt].acc(1,SP) + CB[cnt].acc(1,SP+1) ) / 2;
            CB[cnt].vel(2, SP+1) = CB[cnt].vel(2,SP) + h*( CB[cnt].acc(2,SP) + CB[cnt].acc(2,SP+1) ) / 2;
        }
    }

}

/*
verlet() - The numerical algorithm "Euler"
           Calculates values for next time step
*/
void SolarSystem::euler() {

    vec r_vec_cnt = zeros<vec>(3);
    massCenter();

    // SP = Step Point (time point)
    for (int SP = 0; SP < n-1; SP++) {

        // cnt = current (current celestial body)
        for (int cnt = 0; cnt < size; cnt++) {

            // Creates a temporary r vector for the current body
            r_vec_cnt(0) = CB[cnt].pos(0,SP); r_vec_cnt(1) = CB[cnt].pos(1,SP); r_vec_cnt(2) = CB[cnt].pos(2,SP);

            CB[cnt].acc(0, SP) = gravitation(SP, cnt, r_vec_cnt, 0)/CB[cnt].mass;
            CB[cnt].acc(1, SP) = gravitation(SP, cnt, r_vec_cnt, 1)/CB[cnt].mass;
            CB[cnt].acc(2, SP) = gravitation(SP, cnt, r_vec_cnt, 2)/CB[cnt].mass;

            CB[cnt].vel(0, SP+1) = CB[cnt].vel(0, SP) + CB[cnt].acc(0, SP)*h;
            CB[cnt].vel(1, SP+1) = CB[cnt].vel(1, SP) + CB[cnt].acc(1, SP)*h;
            CB[cnt].vel(2, SP+1) = CB[cnt].vel(2, SP) + CB[cnt].acc(2, SP)*h;

            CB[cnt].pos(0, SP+1) = CB[cnt].pos(0, SP) + CB[cnt].vel(0, SP)*h;
            CB[cnt].pos(1, SP+1) = CB[cnt].pos(1, SP) + CB[cnt].vel(1, SP)*h;
            CB[cnt].pos(2, SP+1) = CB[cnt].pos(2, SP) + CB[cnt].vel(2, SP)*h;
        }
    }

}

/*
writeValuesToFile() - writes the values of position, velocity and acceleration to a file

Structure:
    x y z vx vy vz ax ay az
    .
    .
    .
    x y z vx vy vz ax ay az
    -
    x y z vx vy vz ax ay az
    .
    .
    .
    x y z vx vy vz ax ay az

    Each "-" signals a new body

Parameters:
    filename - name to give to file

Python script assumes filename to be "values.txt"
*/
void SolarSystem::writeValuesToFile(string filename) {

    ofstream my_file;
    my_file.open(filename);
    char a = 45;

    for (int i = 0; i < size; i++) {

        my_file << a << endl;

        for (int j = 0; j < n-1; j++) {
            my_file << CB[i].pos(0,j) << " " << CB[i].pos(1,j) << " " << CB[i].pos(2,j);
            my_file << " ";
            my_file << CB[i].vel(0,j) << " " << CB[i].vel(1,j) << " " << CB[i].vel(2,j);
            my_file << " ";
            my_file << CB[i].acc(0,j) << " " << CB[i].acc(1,j) << " " << CB[i].acc(2,j) << endl;
        }
    }

    my_file.close();

}

/*
writePlotInfo() - writes the name of the bodies to file

Strucuture:
    n
    h
    -
    name
    -
    name
    .
    .
    .

Parameters:
    filename - name of file

Python script assumes filename to be "plot_info.txt"
*/
void SolarSystem::writePlotInfo(string filename) {

    char a = 45;

    ofstream my_file;
    my_file.open(filename);
    my_file << n << endl;
    my_file << h << endl;

    for (int i = 0; i < size; i++) {

        my_file << CB[i].name << endl;
        my_file << a << endl;
    }

    my_file.close();

}

