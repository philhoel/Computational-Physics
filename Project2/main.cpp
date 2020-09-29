#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iostream>
#include "time.h"
#include <armadillo>
#include "LinearSystem.hpp"

using namespace std;
using namespace arma;

int main() {

    LinSys test_obj(10);
    //LinSys test_obj2(300, 5);
    
    vec eigval;
    mat eigvec;

    //eig_sym(eigval, eigvec, test_obj.A);

    /*

    ofstream new_file;
    new_file.open("this_file.txt");
    for (int i = 0; i < 300; i++) {
        new_file << eigvec[i] << endl;
    }
    new_file.close();

    */

   test_obj.iterations();
   test_obj.extract_eigenvalues();
   test_obj.sort_eig();
   test_obj.pretty_print();




    return 0;
}