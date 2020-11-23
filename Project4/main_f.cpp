#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>

#include "isingmodel.hpp"

void WriteToFile(vector<vector<double> >& vec, int counter, string filename);

int main(int argc, char *argv[]) {

    double initial_temp, final_temp, temp_step;
    int n, mcs;
    double norm;

    initial_temp = atof(argv[1]);
    final_temp = atof(argv[2]);
    temp_step = atof(argv[3]);
    n = atoi(argv[4]);
    mcs = atoi(argv[5]);

    norm = 1./mcs;
    string file = argv[6];
    int counter = 0;

    vector<double> E;
    vector<double> E2;
    vector<double> M;
    vector<double> M2;
    vector<double> Mabs;
    vector<double> temperature;

    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp);
        model.MonteCarlo(mcs);

        E.push_back(model.average[0]*norm/pow(n,2));
        E2.push_back(model.average[1]*norm);
        M.push_back(model.average[2]*norm/pow(n,2));
        M2.push_back(model.average[3]*norm);
        Mabs.push_back(model.average[4]*norm);
        temperature.push_back(temp);

        counter++;
        
    }

    vector<vector<double> > vec;

    vec.push_back(E);
    vec.push_back(E2);
    vec.push_back(M);
    vec.push_back(M2);
    vec.push_back(Mabs);
    vec.push_back(temperature);

    WriteToFile(vec, counter, file);

    return 0;
}

void WriteToFile(vector<vector<double> >& vec, int counter, string filename) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "E, E2, M, M2, Mabs, Temp" << endl;
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
        myfile << ",";
        myfile << vec[5][j];
        myfile << endl;
    }
    myfile.close();
}