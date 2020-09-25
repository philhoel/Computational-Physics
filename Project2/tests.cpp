#include <cmath>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include "LinearSystem.hpp"

using namespace std;
using namespace arma;

/*
Tests if offdiag() finds the biggest non-diagonal
number in the matrix.
*/
void test_maxnondiag() {

    double tolerance = 1E-12;
    double computed_max;
    double expected_max = 10000;


    LinSys test_obj(100, true);

    test_obj.offdiag(100);

    computed_max = test_obj.get_maxnondiag();

    assert (abs(expected_max - computed_max) < tolerance);
}

int main() {

    test_maxnondiag();

    return 0;
}