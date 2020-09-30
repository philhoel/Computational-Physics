#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iostream>
#include "time.h"
#include <armadillo>
#include "LinearSystem.hpp"

using namespace std;
using namespace arma;

void multiple_rho(double rho);

int main() {
    
    /*

    //To plot assignment e
    //-----------------------------------------------------//

    LinSys test_obj1(300, 5, 0.01);
    LinSys test_obj2(300, 5, 0.5);
    LinSys test_obj3(300, 5, 1);
    LinSys test_obj4(300, 5, 5);
    
    vec eigval;
    mat eigvec;

    eig_sym(eigval, eigvec, test_obj1.A);
    
    
    ofstream new_file;
    new_file.open("this_file.txt");
    for (int i = 0; i < 300; i++) {
        new_file << eigvec[i] << endl;
    }
    new_file.close();

    vec eigval2;
    mat eigvec2;

    eig_sym(eigval2, eigvec2, test_obj2.A);
    

    ofstream new_file2;
    new_file2.open("this_file2.txt");
    for (int i = 0; i < 300; i++) {
        new_file2 << eigvec2[i] << endl;
    }
    new_file2.close();

    vec eigval3;
    mat eigvec3;

    eig_sym(eigval3, eigvec3, test_obj3.A);
    

    ofstream new_file3;
    new_file3.open("this_file3.txt");
    for (int i = 0; i < 300; i++) {
        new_file3 << eigvec3[i] << endl;
    }
    new_file3.close();

    vec eigval4;
    mat eigvec4;

    eig_sym(eigval4, eigvec4, test_obj4.A);
    

    ofstream new_file4;
    new_file4.open("this_file4.txt");
    for (int i = 0; i < 300; i++) {
        new_file4 << eigvec4[i] << endl;
    }
    new_file4.close();

    system("python3 python_plot.py this_file.txt this_file2.txt this_file3.txt this_file4.txt 5");

    //------------------------------------------------------//
    */

  /*
  //To print eigenvalues for assignemnt b
  //--------------------------------------------------------//

  LinSys test_obj(300);
  cout << "Analytic" << endl;
  test_obj.analyticEig();
  test_obj.print_anaEig();
  test_obj.iterations();
  test_obj.extract_eigenvalues();
  test_obj.sort_eig();
  cout << "Numerical" << endl;
  test_obj.pretty_print();

  cout << "eig_sym" << endl;

  for (int i = 0; i < 5; i++) {
      cout << eigval[i] << endl;
  }
  
  //------------------------------------------------------------//
  */

  /*
  //Plotting eigenvector of lowest eigenvalue for buckling beam
  //--------------------------------------------------------------//

  LinSys test_obj(300);

  vec eigval;
  mat eigvec;
  eig_sym(eigval, eigvec, test_obj.A);

  ofstream new_file_a;
  new_file_a.open("new_file.txt");
  for (int i = 0; i < 300; i++) {
      new_file_a << eigvec[i] << endl;
  }
  new_file_a.close();

  system("python3 python_plot2.py new_file.txt 1");
  
  //------------------------------------------------------------//
  */

  /*
  //To print eigenvalues for assignment d
  //------------------------------------------------------------//

  LinSys test_obj_a(300, 5);
  test_obj.iterations();
  test_obj.extract_eigenvalues();
  test_obj.sort_eig();
  cout << "Numerical" << endl;
  test_obj.pretty_print();

  cout << "eig_sym" << endl;

  for (int i = 0; i < 5; i++) {
      cout << eigval[i] << endl;
  }
  
  //------------------------------------------------------------//
  */

  /*
  //Plotting eigenvector for assignment d
  //---------------------------------------------------------------//

  LinSys test_obj_b(300, 5);

  vec eigval;
  mat eigvec;
  eig_sym(eigval, eigvec, test_obj_b.A);

  ofstream new_file_b;
  new_file_b.open("new_file2.txt");
  for (int i = 0; i < 300; i++) {
      new_file_b << eigvec[i] << endl;
  }
  new_file_b.close();

  system("python3 python_plot2.py new_file2.txt 5")
  
  //-----------------------------------------------------------------//
  */

  /*
  
  //Testing multiple rho (very slow)
  //----------------------------------------------------------------//
  

  for (double i = 4; i <= 6; i += 0.5) {
      
      multiple_rho(i);
  }

  //-----------------------------------------------------------------//
  
  */
  
  /*
  //Testing runtime
  //--------------------------------------------------------------//
  
    LinSys new_obj1(100,5);
    LinSys new_obj2(200,5);
    LinSys new_obj3(300,5);

    clock_t start1, start2, start3, finish1, finish2, finish3;

    start1 = clock();
    new_obj1.iterations();
    finish1 = clock();
    start2 = clock();
    new_obj2.iterations();
    finish2 = clock();
    start3 = clock();
    new_obj3.iterations();
    finish3 = clock();

    cout << "Time: " << (double) (finish1 - start1)/(CLOCKS_PER_SEC) << " | N = 100" << endl;
    cout << "Time: " << (double) (finish2 - start2)/(CLOCKS_PER_SEC) << " | N = 200" << endl;
    cout << "Time: " << (double) (finish3 - start3)/(CLOCKS_PER_SEC) << " | N = 300" << endl;
  
  //------------------------------------------------------------//
  */
  

    return 0;
}

void multiple_rho(double rho) {

    LinSys new_obj1(100, rho);
    LinSys new_obj2(200, rho);
    LinSys new_obj3(300, rho);

    new_obj1.iterations();
    new_obj2.iterations();
    new_obj3.iterations();

    new_obj1.extract_eigenvalues();
    new_obj2.extract_eigenvalues();
    new_obj3.extract_eigenvalues();

    new_obj1.sort_eig();
    new_obj2.sort_eig();
    new_obj3.sort_eig();

    cout << "N = 100 | rho = " << rho << endl;
    new_obj1.pretty_print();
    cout << "N = 200 | rho = " << rho << endl;
    new_obj2.pretty_print();
    cout << "N = 300 | rho = " << rho << endl;
    new_obj3.pretty_print();
}