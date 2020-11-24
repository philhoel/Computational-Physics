#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>
#include <time.h>

#include "isingmodel.hpp"

void WriteToFile(vector<vector<double> >& vec, int counter, string filename, int n, double norm);

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

    vector<double> E;
    vector<double> E2;
    vector<double> M;
    vector<double> M2;
    vector<double> Mabs;
    vector<double> temperature;
    vector<double> Cv;
    vector<double> X;
    vector<double> acc;

    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp);
        model.MonteCarlo(mcs);

        E.push_back(model.average[0]*norm);
        E2.push_back(model.average[1]*norm);
        M.push_back(model.average[2]*norm);
        M2.push_back(model.average[3]*norm);
        Mabs.push_back(model.average[4]*norm);
        temperature.push_back(temp);


        double Evar, Mvar;
        Evar = (E2[counter]-E[counter]*E[counter]);
        Mvar = (M2[counter]-Mabs[counter]*Mabs[counter]);


        Cv.push_back(Evar/(pow(temp,2)*pow(n,2)));
        X.push_back(Mvar/(temp*pow(n,2)));

        acc.push_back(model.acpt_count);

        counter++;
        
    }

    vector<vector<double> > vec;
    vec.push_back(E);
    vec.push_back(Mabs);
    vec.push_back(Cv);
    vec.push_back(X);
    vec.push_back(temperature);
    

    WriteToFile(vec, counter, file, n, norm);

    return 0;
}

void WriteToFile(vector<vector<double> >& vec, int counter, string filename, int n, double norm) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "E, M, CV, X, Temp, acc" << endl;
    for (int j = 0; j < counter; j++) {
        myfile << vec[0][j]/pow(n,2);
        myfile << ",";
        myfile << vec[1][j]/pow(n,2);
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