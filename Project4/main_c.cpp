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

    vector<double> CV;
    vector<double> X;
    vector<double> temperature;
    vector<double> Evariance;
    vector<double> Mvariance;
    vector<double> M;
    vector<double> E;

    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp);
        model.MonteCarlo(mcs);



        CV.push_back(model.average[5]/(temp*temp));
        X.push_back(model.average[6]/temp);
        Evariance.push_back(model.average[5]);
        Mvariance.push_back(model.average[6]);
        E.push_back(model.average[0]);
        M.push_back(model.average[2]);
        temperature.push_back(temp);
        counter++;
        
    }

    vector<vector<double> > vec;
    vec.push_back(E);
    vec.push_back(M);
    vec.push_back(Evariance);
    vec.push_back(Mvariance);
    vec.push_back(CV);
    vec.push_back(X);
    vec.push_back(temperature);
    

    WriteToFile(vec, counter, file);

    return 0;
}

void WriteToFile(vector<vector<double> >& vec, int counter, string filename) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "E, M, E^2, M^2, CV, X, Temp" << endl;
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
        myfile << ",";
        myfile << vec[6][j];
        myfile << endl;
    }
    myfile.close();
}