#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>

#include "isingmodel.hpp"
#include "System.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    srand(time(NULL));

    //System tempChangeProgram(20, 1000000, 2, 2.3, 0.005, "tempValues.csv");
    System constTempProgram(20, 10000, "MCvalues.csv");

    //tempChangeProgram.tempChange();
    constTempProgram.MCtemp(1, 2.4);


    return 0;
}

