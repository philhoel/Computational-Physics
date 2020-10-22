#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

int main() {

    char a = 45;
    cout << a << endl;


    SolarSystem test_obj(1000);
    double PI = test_obj.getPI();


    vec Earth = zeros<vec> (4);
    Earth(0) = 1;
    Earth(1) = 0;
    Earth(2) = 0;
    Earth(3) = 2*PI;

    vec Mars = zeros<vec> (4);
    Mars(0) = 3;
    Mars(1) = 0.5;
    Mars(2) = 0;
    Mars(3) = PI;

    vec Jupiter = zeros<vec> (4);
    Mars(0) = 5;
    Mars(1) = 4;
    Mars(2) = 0;
    Mars(3) = PI;

    vec Venus = zeros<vec> (4);
    Mars(0) = 4;
    Mars(1) = 2;
    Mars(2) = 0;
    Mars(3) = PI;


    test_obj.addPlanet("Earth", 3, Earth, 1);
    //test_obj.addPlanet("Mars", 4, Mars, 0.5);
    //test_obj.addPlanet("Jupiter", 5, Jupiter, 5);
    //test_obj.addPlanet("Venus", 6, Venus, 4);
    test_obj.euler();
    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}