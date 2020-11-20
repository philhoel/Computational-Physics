#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>

#include "isingmodel.hpp"

using namespace std;

void WriteToFile(string filename, int n, vector<vector<double> >& vec, int counter);

void WriteGridToFile(string filename, Ising& model);

int main(int argc, char* argv[]) {

    srand(time(NULL));

    vector<vector<double> > vec;

    vector<double> E;
    vector<double> E2;
    vector<double> M;
    vector<double> M2;
    vector<double> Mabs;
    vector<double> temperature;

    vec.push_back(E);
    vec.push_back(E2);
    vec.push_back(M);
    vec.push_back(M2);
    vec.push_back(Mabs);
    vec.push_back(temperature);

    int mcs = 10000;
    int n = 20;
    double initial_temp = 1;
    double final_temp = 2.4;
    double temp_step = 0.05;

    double norm = 1./mcs;
    int counter = 0; // to count number of interations

    // Main loop
    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising test(n, temp);
        test.MonteCarlo(mcs);

        for (int i = 0; i < 5; i++) {
            vec[i].push_back(test.average[i]*norm);
        }
        
        vec[5].push_back(temp);

        counter++;
        
    }

    WriteToFile("values.csv", n, vec, counter);

    //WriteGridToFile("grid.txt", test);

    //system("python3 read.py grid.txt 20");

    return 0;
}


void WriteToFile(string filename, int n, vector<vector<double> >& vec, int counter) {
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



void WriteGridToFile(string filename, Ising& model) {
    ofstream myfile;
    myfile.open(filename);
    for (int y = 0; y < model.n; y++) {
        for (int x = 0; x < model.n; x++) {
            myfile << model.Grid(x, y);
            myfile << " ";
        }
        myfile << endl;
    }
}