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

    System tempChangeProgram(20, 1000, 2, 2.3, 0.05, "tempValues.csv");
    System constTempProgram(20, 1000, "MCvalues.csv");

    constTempProgram.constTemp(1, 2.4);


    return 0;
}

