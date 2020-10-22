#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

int main() {


    SolarSystem test_obj(1000);
    double PI = test_obj.getPI();


    vec test = zeros<vec> (4);
    test(0) = 1;
    test(1) = 0;
    test(2) = 0;
    test(3) = 2*PI;


    test_obj.addPlanet("Earth", 3, test, 1);
    test_obj.euler();
    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}