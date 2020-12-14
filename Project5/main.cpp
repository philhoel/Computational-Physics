#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <armadillo>

#include "Solver.hpp"

using namespace std;
using namespace arma;


int main() {

    //Solver obj(1000, 10, 0.001);
    //obj.ForwardEuler();
    //obj.WriteToFile("FE.csv");

    Solver obj2(1000, 100, 0.001);
    obj2.BackwardEuler();
    obj2.WriteToFile("BE.csv");

    Solver obj3(1000, 100, 0.001);
    obj3.CrankNicholson();
    obj3.WriteToFile("CN.csv");


}