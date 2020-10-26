#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

int main() {

    SolarSystem test(1000000, 10);
    vector<CelestBody> test_vec;
    double PI = test.PI;

    vec Sun = zeros<vec> (3);
    vec Earth = zeros<vec> (6);

    Earth(0) = 1;
    Earth(1) = 0;
    Earth(2) = 0;
    Earth(3) = 1;
    Earth(4) = 2*PI;
    Earth(5) = 0;

    test.addSun("Sun", 1, Sun);
    test.addBody("Earth", 3e-6, Earth);
    test.verlet();

    test_vec = test.getList();
    int n = test.getN();

    test.energy();

    test.energyConservation(1);

}