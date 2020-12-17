#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <armadillo>

#include "Solver.hpp"
#include "Solver2dim.hpp"

using namespace std;
using namespace arma;


int main() {

    //Solver obj(200, 10000, 0.00001);
    //obj.ForwardEuler();
    //obj.WriteToFile("FE.csv");

    //Solver obj2(100000, 100, 0.001);
    //obj2.BackwardEuler();
    //obj2.WriteToFile("BE.csv");

    //Solver obj3(10000, 100, 0.001);
    //obj3.CrankNicholson();
    //obj3.WriteToFile("CN.csv");

    Solver2dim obj2D(200, 1000, 0.00001);
    obj2D.ExplicitScheme();
    //obj2D.ForwardEuler(10, 100, 500, 999);
    obj2D.WriteToMultipleFiles("2DEuler_50.csv", "2DEuler_100.csv", "2DEuler_500.csv", "2DEuler_999.csv");


}