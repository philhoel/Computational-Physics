#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

int main() {

    SolarSystem test_obj(1000, 1);
    test_obj.addPlanet("Earth", 3);
    test_obj.euler();
    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}