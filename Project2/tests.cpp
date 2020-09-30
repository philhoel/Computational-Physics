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
    double expected_max = 36;


    LinSys test_obj(5);

    test_obj.offdiag(5);

    computed_max = test_obj.get_maxnondiag();

    cout << computed_max << endl;

    assert (abs(expected_max - computed_max) < tolerance);
}

void test_eigenvalues() {

    double tolerance = 1E-3;


    LinSys test_obj(5);

    vec eigval;

    eig_sym(eigval, test_obj.A);

    test_obj.iterations();
    test_obj.extract_eigenvalues();

    for (int i = 0; i < 5; i++) {
        assert (abs(eigval[i] - test_obj.eig[i]) > tolerance);
    }
}


int main() {

    test_maxnondiag();
    test_eigenvalues();

    return 0;
}