#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>

#include "solarsystem.hpp"

using namespace std;
using namespace arma;

void NASA_values(vec &Sun, vec &Earth, vec &Jupiter, vec &Mars,vec &Saturn, vec &Venus, vec &Mercury, vec &Uranus, vec &Neptune, vec &Pluto);
void initial_values(vec &S, vec &E, vec &J, vec &Mer, vec &V, vec &M, vec &Sat, vec &U, vec &N, double pi);


int main(int argc, char *argv[]) {

    int n = atoi(argv[2]);
    double t = atof(argv[3]);
    double mass = atof(argv[5]);

    //int n = 2000;
    //double t = 12;
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
    vec P;


    vec Sun;
    vec Mars;
    vec Venus;
    vec Earth;
    vec Mercury;
    vec Jupiter;
    vec Saturn;
    vec Uranus;
    vec Neptune;
    vec Pluto;

    NASA_values(Sun, Earth, Jupiter, Mars, Saturn, Venus, Mercury, Uranus, Neptune, Pluto);
    initial_values(S, E, J, Mer, V, M, Sat, U, N, PI);
    string input= argv[6];
    test_obj.addSun("Sun", 1.0, S);
    if(input == "a"){
        test_obj.addBody("Earth", 3e-6, E);
    }else if(input == "b"){
        test_obj.addBody("Earth", 3e-6, E);
        test_obj.addBody("Jupiter", mass, J);
    }else if(input == "c"){
        test_obj.addBody("Earth", 3e-6, Earth);
        test_obj.addBody("Jupiter", mass, Jupiter);
        test_obj.addBody("Mercury", 1.66e-7, Mercury);
        test_obj.addBody("Venus", 2.44e-6, Venus);
        test_obj.addBody("Mars", 3.22e-7, Mars);
        test_obj.addBody("Saturn", 2.86e-4, Saturn);
        test_obj.addBody("Uranus", 4.37e-5, Uranus);
        test_obj.addBody("Neptune", 5.13e-5, Neptune);
        test_obj.addBody("Pluto", 6.55e-9, Pluto);
    }
    /*test_obj.addBody("Jupiter", 9.54e-4, Jupiter);
    test_obj.addBody("Mars", 3.22e-7, Mars);
    test_obj.addBody("Venus", 2.44e-6, Venus);
    test_obj.addBody("Mercury", 1.66e-7, Mercury);
    test_obj.addBody("Uranus", 4.37e-5, Uranus);
    test_obj.addBody("Neptune", 5.13e-5, Neptune);
    test_obj.addBody("Pluto", 6.55e-9, Pluto);*/

    /*test_obj.addBody("Mercury", 1.66e-7, Mer);
    test_obj.addBody("Venus", 2.44e-6, V);
    test_obj.addBody("Mars", 3.22e-7, M);
    test_obj.addBody("Jupiter", mass, J);
    test_obj.addBody("Saturn", 2.86e-4, Sat);
    test_obj.addBody("Uranus", 4.37e-5, U);
    test_obj.addBody("Neptune", 5.13e-5, N);*/
    string input2 = argv[4];
    if(input2 == "euler"){
        test_obj.euler();
    }else if(input2 == "verlet"){
        test_obj.verlet();
    }


    //test_obj.euler();

    //test_obj.verlet();

    test_obj.writePlotInfo("plot_info.txt");
    test_obj.writeValuesToFile("values.txt");
}

void NASA_values(vec &Sun, vec &Earth, vec &Jupiter, vec &Mars,vec &Saturn, vec &Venus, vec &Mercury, vec &Uranus, vec &Neptune, vec &Pluto) {

    Sun = zeros<vec> (6);
    Sun(0) = -6.158727289643375E-03;
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

    Mars = zeros<vec> (6);
    Mars(0) = 1.272214290981063E+00;
    Mars(1) = 6.357061456746934E-01;
    Mars(2) = -1.808172669799765E-02;
    Mars(3) = -5.652727216112586E-03 * 365.25;
    Mars(4) = 1.374427785658439E-02 * 365.25;
    Mars(5) = 4.268480851211387E-04 * 365.25;

    Saturn = zeros<vec> (6);
    Saturn(0) = 5.175292350241609E+00;
    Saturn(1) = -8.543633656588499E+00;
    Saturn(2) = -5.748143340428273E-02;
    Saturn(3) = 4.461143391357680E-03 * 365.25;
    Saturn(4) = 2.875435986042164E-03 * 365.25;
    Saturn(5) = -2.273055269610145E-04 * 365.25;

    Venus = zeros<vec> (6);
    Venus(0) = -3.514928287195656E-01;
    Venus(1) = 6.358488172813552E-01;
    Venus(2) = 2.865648089021929E-02;
    Venus(3) = -1.780881548732578E-02 * 365.25;
    Venus(4) = -9.846986326668720E-03 * 365.25;
    Venus(5) = 8.924181175967461E-04 * 365.25;

    Mercury = zeros<vec> (6);
    Mercury(0) = 3.143670922315332E-01;
    Mercury(1) = 1.065411264192840E-01;
    Mercury(2) = -2.112751089263323E-02;
    Mercury(3) = -1.385295914052545E-02 * 365.25;
    Mercury(4) = 2.810197115234333E-02 * 365.25;
    Mercury(5) = 3.567096140614040E-03 * 365.25;

    Uranus = zeros<vec> (6);
    Uranus(0) = 1.551758289636478E+01;
    Uranus(1) = 1.226559872169746E+01;
    Uranus(2) = -1.554773476982917E-01;
    Uranus(3) = -2.467768113603644E-03 * 365.25;
    Uranus(4) = 2.902311949265869E-03 * 365.25;
    Uranus(5) = 4.277562887275033E-05 * 365.25;

    Neptune = zeros<vec> (6);
    Neptune(0) = 2.941614517618505E+01;
    Neptune(1) = -5.443342600803682E+00;
    Neptune(2) = -5.658299106997762E-01;
    Neptune(3) = 5.501849215323422E-04 * 365.25;
    Neptune(4) = 3.105652684445751E-03 * 365.25;
    Neptune(5) = -7.622466166465130E-05 * 365.25;

    Pluto = zeros<vec> (6);
    Pluto(0) = 1.384827010175508E+01;
    Pluto(1) = -3.119498202697125E+01;
    Pluto(2) = -6.676791489395038E-01;
    Pluto(3) = 2.952319305045842E-03 * 365.25;
    Pluto(4) = 6.077063426811567E-04 * 365.25;
    Pluto(5) = -9.227677900255182E-04 * 365.25;

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
   Sun(0) = -6.158727289643375E-03;
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
