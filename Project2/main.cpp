#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include "time.h"
#include <armadillo>
#include "LinearSystem.hpp"

using namespace std;
using namespace arma;

int main() {

    LinSys test_obj(100);
    LinSys test_obj2(100, 5);

    //test_obj.iterations(100);
    //test_obj.extract_eigenvalues();
    //test_obj.print_eigenvalues();

    test_obj2.iterations(100);
    test_obj2.extract_eigenvalues();
    test_obj2.print_eigenvalues();
    
}