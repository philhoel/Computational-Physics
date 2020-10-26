#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

void NASA_values(vec &Sun, vec &Earth, vec &Jupiter);
void initial_values(vec &S, vec &E, vec &J, vec &Mer, vec &V, vec &M, vec &Sat, vec &U, vec &N, double pi);


int main(int argc, char *argv[]) {

    int n = (int) argv[2];
    double t = (double) argv[3];
    double mass = (double) argv[5];


    SolarSystem test_obj(n, t);
    double PI = test_obj.PI;

    vec S;
    vec Mer;
    vec V;
    vec E;
    vec M;
    vec J;
    vec Sat;
    vec U;
    vec N;

    vec Sun;
    vec Mercury;
    vec Venus;
    vec Earth;
    vec Mars;
    vec Jupiter;
    vec Saturn;
    vec Uranus;
    vec Neptune;

    NASA_values(Sun, Earth, Jupiter);
    initial_values(S, E, J, Mer, V, M, Sat, U, N, PI);

    test_obj.addSun("Sun", 1.0, S);

    if (argv[6] == "a") {
        test_obj.addBody("Earth", 3e-6, E);
    } else if (argv[6] == "b") {
        test_obj.addBody("Earth", 3e-6, E);
        // mass = 9.54e-4
        test_obj.addBody("Jupiter", mass, J);
    } else if (argv[6] == "c") {
        test_obj.addBody("Mercury", 1.66e-7, Mer);
        test_obj.addBody("Venus", 2.44e-6, V);
        test_obj.addBody("Earth", 3e-6, E);
        test_obj.addBody("Mars", 3.22e-7, M);
        test_obj.addBody("Jupiter", mass, J);
        test_obj.addBody("Saturn", 2.86e-4, Sat);
        test_obj.addBody("Uranus", 4.37e-5, U);
        test_obj.addBody("Neptune", 5.13e-5, N);
    }
    
    if (argv[4] == "euler") {
        test_obj.euler();
    } else if (argv[4] == "verlet") {
        test_obj.verlet();
    }

    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}

void NASA_values(vec &Sun, vec &Earth, vec &Jupiter) {

    Sun = zeros<vec> (6);
    Sun(0) = -6.158727289643375E-0;
    Sun(1) = 6.384843795818435E-03;
    Sun(2) = 9.046249474982092E-05;
    Sun(3) = -7.234332664219356E-06 * 365.25;
    Sun(4) = -5.148288747422735E-06 * 365.25;
    Sun(5) = 2.176403647237366E-07 * 265.25;

    Earth = zeros<vec> (6);
    Earth(0) = 8.575473846476438E-01;
    Earth(1) = 5.002546898150230E-01;
    Earth(2) = 6.633031806521973E-05;
    Earth(3) = -8.833785441020210E-03 * 365.25;
    Earth(4) = 1.486318699072101E-02 * 365.25;
    Earth(5) = 1.132388155993301E-07 * 365.25;

    Jupiter = zeros<vec> (6);
    Jupiter(0) = 2.601611179783377E+00;
    Jupiter(1) = -4.399440200989516E+00;
    Jupiter(2) = -3.995501635215625E-02;
    Jupiter(3) = 6.402308693680906E-03 * 365.25;
    Jupiter(4) = 4.198441133967116E-03 * 365.25;
    Jupiter(5) = -1.606688854250781E-04 * 365.25;

}

void initial_values(vec &S, vec &E, vec &J, vec &Mer, vec &V, vec &M, vec &Sat, vec &U, vec &N, double pi) {
    S = zeros<vec> (3);
    S(0) = 0;
    S(1) = 0;
    S(2) = 0;

    Mer = zeros<vec> (6);
    Mer(0) = 0.39;
    Mer(3) = 1.5;
    Mer(4) = 2.5*pi;

    V = zeros<vec> (6);
    V(0) = 0.72;
    V(3) = 0.7;
    V(4) = 2*pi;

    E = zeros<vec> (6);
    E(0) = 1;
    E(1) = 0;
    E(2) = 0;
    E(3) = 1;
    E(4) = 2*pi;
    E(5) = 0;

    M = zeros<vec> (6);
    M(0) = 1.52;
    M(3) = 0.7;
    M(4) = 1.5*pi;
    
    J = zeros<vec> (6);
    J(0) = 5.2;
    J(1) = 0;
    J(2) = 0;
    J(3) = 0.5;
    J(4) = 2.5;

    Sat = zeros<vec> (6);
    Sat(0) = 9.54;
    Sat(3) = 0.4;
    Sat(4) = 2;

    U = zeros<vec> (6);
    U(0) = 19.19;
    U(3) = 0.2;
    U(4) = 1.4;

    N = zeros<vec> (6);
    N(0) = 30.06;
    N(3) = 0.2;
    N(4) = 1.17;
}

/*
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
*/