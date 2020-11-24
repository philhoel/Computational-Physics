#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>
#include <time.h>

#include "isingmodel.hpp"

void WriteToFile(vector<vector<double> >& vec, int counter, string filename, int n);

int main(int argc, char *argv[]) {

    srand(time(NULL));

    cout << "RAND_MAX = " << RAND_MAX << endl;

    double initial_temp, final_temp, temp_step;
    int n, mcs;
    double norm;
    double temp;
    initial_temp = atof(argv[1]);
    final_temp = atof(argv[2]);
    temp_step = atof(argv[3]);
    n = atoi(argv[4]);
    mcs = atoi(argv[5]);
    //temp = atof(argv[3]);

    norm = 1./mcs;
    string file = argv[6];
    int counter = 0;

    vector<double> CV;
    vector<double> X;
    vector<double> temperature;
    vector<double> Mabs;
    vector<double> E;

    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp);
        model.MonteCarlo(mcs);

        double E_ = model.average[0]*norm/pow(n,2);
        double Mabs_ = model.average[4]*norm/pow(n,2);

        E.push_back(E_);
        Mabs.push_back(Mabs_);

        double E2 = model.average[1]*norm/pow(n,4);
        double M2 = model.average[3]*norm/pow(n,4);
        
        CV.push_back((E2-E_*E_)/pow(temp,2));
        X.push_back((M2 - Mabs_*Mabs_)/temp);
        temperature.push_back(temp);
        counter++;
        
    }

    vector<vector<double> > vec;
    vec.push_back(E);
    vec.push_back(Mabs);
    vec.push_back(CV);
    vec.push_back(X);
    vec.push_back(temperature);
    

    WriteToFile(vec, counter, file, n);

    return 0;
}

void WriteToFile(vector<vector<double> >& vec, int counter, string filename, int n) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "E, M, CV, X, Temp" << endl;
    for (int j = 0; j < counter; j++) {
        myfile << vec[0][j];
        myfile << ",";
        myfile << vec[1][j];
        myfile << ",";
        myfile << vec[2][j];
        myfile << ",";
        myfile << vec[3][j];
        myfile << ",";
        myfile << vec[4][j];
        myfile << endl;
    }
    myfile.close();
}