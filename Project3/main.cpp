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


    SolarSystem test_obj(1000, 11.86);
    double PI = test_obj.getPI();

    /*
    vec Earth = zeros<vec> (4);
    Earth(0) = 1;
    Earth(1) = 0;
    Earth(2) = 0;
    Earth(3) = 2*PI;
    */
    

   vec Sun = zeros<vec> (4);
   Sun(0) = -6.158727289643375E-0;
   Sun(1) = 6.384843795818435E-03;

   
    vec Earth = zeros<vec> (4);
    Earth(0) = 8.575473846476438E-01;
    Earth(1) = 5.002546898150230E-01;
    Earth(2) = -8.833785441020210E-03 * 365.25;
    Earth(3) = 1.486318699072101E-02 * 365.25;
    
    

    vec Mars = zeros<vec> (4);
    Mars(0) = 1.272214290981063E+00;
    Mars(1) = 6.357061456746934E-01;
    Mars(2) = -5.652727216112586E-03;
    Mars(3) = 1.374427785658439E-02;

    vec Jupiter = zeros<vec> (4);
    Jupiter(0) = 2.601611179783377E+00;
    Jupiter(1) = -4.399440200989516E+00;
    Jupiter(2) = 6.402308693680906E-03 * 365.25;
    Jupiter(3) = 4.198441133967116E-03 * 365.25;

    vec Venus = zeros<vec> (4);
    Venus(0) = 4;
    Venus(1) = 2;
    Venus(2) = 0;
    Venus(3) = PI;

    test_obj.addPlanet("Sun", 0, Sun, 1);
    //test_obj.addPlanet("Earth", 3, Earth, 1);
    //test_obj.addPlanet("Mars", 4, Mars, 0.5);
    test_obj.addPlanet("Jupiter", 5, Jupiter, 9.54e-4);
    //test_obj.addPlanet("Venus", 6, Venus, 4);
    //test_obj.euler();
    test_obj.verlet();
    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}