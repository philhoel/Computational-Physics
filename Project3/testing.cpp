#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

void energyConservation(CelestBody planet, int n);

int main() {

    SolarSystem test(1000000, 10);
    vector<CelestBody> test_vec;

    vec Sun = zeros<vec> (3);
    vec Earth = zeros<vec> (6);

    test.addSun("Sun", 1, Sun);
    test.addBody("Earth", 3e-6, Earth);
    test.verlet();

    test_vec = test.getList();
    int n = test.getN();

    energyConservation(test_vec[1], n);

}

void energyConservation(CelestBody planet, int n) {

    double tol = 1e-12;

    double max_x_1 = 0;
    double max_y_1 = 0;
    double max_x_2 = 0;
    double max_y_2 = 0;
    for (int i = 0; i < n/2; i++) {
        if (planet.pos(0,i) > max_x_1 && planet.pos(1,i) > max_y_1) {
            max_x_1  = planet.pos(0,i);
            max_y_1 = planet.pos(1,i);
        }
    }

    for (int i = n/2 +1; i < n; i++) {
        if (planet.pos(0,i) > max_x_2 && planet.pos(1,i) > max_y_2) {
            max_x_2  = planet.pos(0,i);
            max_y_2 = planet.pos(1,i);
        }
    }

    assert( (max_x_1 - max_x_2 < tol) && (max_y_1 - max_y_2 < tol));
}