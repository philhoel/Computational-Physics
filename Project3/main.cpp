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


    SolarSystem test_obj(1000, 10);
    double PI = test_obj.PI;

    /*
    vec Earth = zeros<vec> (4);
    Earth(0) = 1;
    Earth(1) = 0;
    Earth(2) = 0;
    Earth(3) = 2*PI;
    */
    
    // Values taken from NASA, positions taken directly (Should be in AU) 
    // and velocities taken and multiplied with number of days per year

   vec Sun = zeros<vec> (3);
   Sun(0) = -6.158727289643375E-0;
   Sun(1) = 6.384843795818435E-03;
   Sun(2) = 9.046249474982092E-05;

   
    vec Earth = zeros<vec> (6);
    Earth(0) = 8.575473846476438E-01;
    Earth(1) = 5.002546898150230E-01;
    Earth(2) = 6.633031806521973E-05;
    Earth(3) = -8.833785441020210E-03 * 365.25;
    Earth(4) = 1.486318699072101E-02 * 365.25;
    Earth(5) = 1.132388155993301E-07 * 365.25;

    vec Jupiter = zeros<vec> (6);
    Jupiter(0) = 2.601611179783377E+00;
    Jupiter(1) = -4.399440200989516E+00;
    Jupiter(2) = -3.995501635215625E-02;
    Jupiter(3) = 6.402308693680906E-03 * 365.25;
    Jupiter(4) = 4.198441133967116E-03 * 365.25;
    Jupiter(5) = -1.606688854250781E-04 * 365.25;

    vec Mars = zeros<vec> (6);
    Mars(0) = 2.601611179783377E+00;
    Mars(1) = -4.399440200989516E+00;
    Mars(2) = -3.995501635215625E-02;
    Mars(3) = 6.402308693680906E-03 * 365.25;
    Mars(4) = 4.198441133967116E-03 * 365.25;
    Mars(5) = -1.606688854250781E-04 * 365.25;

    vec Venus = zeros<vec> (6);
    Venus(0) = 2.601611179783377E+00;
    Venus(1) = -4.399440200989516E+00;
    Venus(2) = -3.995501635215625E-02;
    Venus(3) = 6.402308693680906E-03 * 365.25;
    Venus(4) = 4.198441133967116E-03 * 365.25;
    Venus(5) = -1.606688854250781E-04 * 365.25;

    vec Saturn = zeros<vec> (6);
    Saturn(0) = 2.601611179783377E+00;
    Saturn(1) = -4.399440200989516E+00;
    Saturn(2) = -3.995501635215625E-02;
    Saturn(3) = 6.402308693680906E-03 * 365.25;
    Saturn(4) = 4.198441133967116E-03 * 365.25;
    Saturn(5) = -1.606688854250781E-04 * 365.25;

    vec Uranus = zeros<vec> (6);
    Uranus(0) = 2.601611179783377E+00;
    Uranus(1) = -4.399440200989516E+00;
    Uranus(2) = -3.995501635215625E-02;
    Uranus(3) = 6.402308693680906E-03 * 365.25;
    Uranus(4) = 4.198441133967116E-03 * 365.25;
    Uranus(5) = -1.606688854250781E-04 * 365.25;

    vec Neptun = zeros<vec> (6);
    Neptun(0) = 2.601611179783377E+00;
    Neptun(1) = -4.399440200989516E+00;
    Neptun(2) = -3.995501635215625E-02;
    Neptun(3) = 6.402308693680906E-03 * 365.25;
    Neptun(4) = 4.198441133967116E-03 * 365.25;
    Neptun(5) = -1.606688854250781E-04 * 365.25;

    vec Mercury = zeros<vec> (6);
    Mercury(0) = 2.601611179783377E+00;
    Mercury(1) = -4.399440200989516E+00;
    Mercury(2) = -3.995501635215625E-02;
    Mercury(3) = 6.402308693680906E-03 * 365.25;
    Mercury(4) = 4.198441133967116E-03 * 365.25;
    Mercury(5) = -1.606688854250781E-04 * 365.25;

    vec Pluto = zeros<vec> (6);
    Pluto(0) = 2.601611179783377E+00;
    Pluto(1) = -4.399440200989516E+00;
    Pluto(2) = -3.995501635215625E-02;
    Pluto(3) = 6.402308693680906E-03 * 365.25;
    Pluto(4) = 4.198441133967116E-03 * 365.25;
    Pluto(5) = -1.606688854250781E-04 * 365.25;

    test_obj.addSun("Sun", 1, Sun);
    test_obj.addBody("Earth", 3e-6, Earth);
    test_obj.addBody("Jupiter", 9.54e-4, Jupiter);
    //test_obj.euler();
    test_obj.verlet();
    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}