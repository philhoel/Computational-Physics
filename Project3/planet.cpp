#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <armadillo>
#include "planet.hpp"

using namespace std;
using namespace arma;

Planet::Planet(string Name, int id) {
    name = Name;
    ID = id;
    pos = zeros<mat> (2, n);
    vel = zeros<mat> (2, n);
    acc = zeros<mat> (2, n);
}

Planet::update_r(int i) {
    r = sqrt(pos(0,i)*pos(0,i) + pos(1,i)*pos(1,i));
}

Planet::getForce() {
    return force;
}

Planet::setForce(double F) {
    force = F;
}

Planet::getName() {
    return name;
}

Planet::getID() {
    return ID;
}