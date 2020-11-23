#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>

#include "isingmodel.hpp"
#include "System.hpp"

System::System(int N, int MCS, double i_temp, double f_temp, double t_step, string fname) {
    
    initial_temp = i_temp;
    final_temp = f_temp;
    temp_step = t_step;
    n = N;
    mcs = MCS;
    filename = fname;
    counter = 0;
    norm = 1./mcs;

}

System::System(int N, int MCS, string fname) {
    n = N;
    mcs = MCS;
    filename = fname;
    counter = 0;
    norm = 1./mcs;
}

void System::tempChange() {

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
        M.push_back(model.average[2]*norm);
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

    WriteToFile(vec);
}

void System::MCtemp(double low, double high) {

    ave = zeros<mat> (8, 7);
    int j = 0;

    for (int i = 1; i < mcs; i*=10) {
        Ising model(n, low);
        Ising model2(n, high);
        Ising model3(n, low, false);
        Ising model4(n, high, false);
        model.MonteCarlo(mcs, true);
        model2.MonteCarlo(mcs, true);
        model3.MonteCarlo(mcs, true);
        model4.MonteCarlo(mcs, true);

        double newNorm = 1./i;

        ave(0, j) = model.average[0]*newNorm;
        ave(1, j) = model2.average[0]*newNorm;
        ave(2, j) = model3.average[0]*newNorm;
        ave(3, j) = model4.average[0]*newNorm;
        ave(4, j) = model.average[1]*newNorm;
        ave(5, j) = model2.average[1]*newNorm;
        ave(6, j) = model3.average[1]*newNorm;
        ave(7, j) = model4.average[1]*newNorm;

        j++;

    }

    ave = ave/pow(n,2);
    WriteMCToFile();
    
}

/*
void System::constTemp(double low, double high) {

    Ising model(n, low);
    Ising model2(n, high);
    Ising model3(n, low, false);
    Ising model4(n, high, false);
    model.MonteCarlo(mcs, true, norm);
    model2.MonteCarlo(mcs, true, norm);
    model3.MonteCarlo(mcs, true, norm);
    model4.MonteCarlo(mcs, true, norm);

    WriteMCToFile(model, model2, model3, model4);
    //cout << model.Eave[3] << endl;

}
*/

void System::WriteToFile(vector<vector<double> >& vec) {

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

void System::WriteMCToFile() {

    ofstream myfile;
    myfile.open(filename);
    myfile << "EO_low, EO_high, EU_low, EU_high, MO_low, MO_high, MU_low, MU_high" << endl;
    for (int i = 0; i < 7; i++) {
        myfile << ave(0, i);
        myfile << ",";
        myfile << ave(1,i);
        myfile << ",";
        myfile << ave(2,i);
        myfile << ",";
        myfile << ave(3,i);
        myfile << ",";
        myfile << ave(4,i);
        myfile << ",";
        myfile << ave(5,i);
        myfile << ",";
        myfile << ave(6,i);
        myfile << ",";
        myfile << ave(7,i);
        myfile << endl;
    }

}

/*

void System::WriteMCToFile(Ising& obj, Ising& obj2, Ising& obj3, Ising& obj4) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "EO_low, EO_high, EU_low, EU_high, MO_low, MO_high, MU_low, MU_high" << endl;
    for (int i = 0; i < mcs; i++) {
        myfile << obj.Eave[i];
        myfile << ",";
        myfile << obj2.Eave[i];
        myfile << ",";
        myfile << obj3.Eave[i];
        myfile << ",";
        myfile << obj4.Eave[i];
        myfile << ",";
        myfile << obj.Mave[i];
        myfile << ",";
        myfile << obj2.Mave[i];
        myfile << ",";
        myfile << obj3.Mave[i];
        myfile << ",";
        myfile << obj4.Mave[i];
        myfile << endl;
    }

}

*/