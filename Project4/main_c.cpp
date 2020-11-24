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
double analyticE(double temp);
double analyticM(double temp);

int main(int argc, char *argv[]) {

    srand(time(NULL));

    cout << "RAND_MAX = " << RAND_MAX << endl;

    double initial_temp, final_temp, temp_step;
    int n, mcs;
    double norm;
    double temp = 4;
    //initial_temp = atof(argv[1]);
    //final_temp = atof(argv[2]);
    //temp_step = atof(argv[3]);
    n = atoi(argv[1]);
    mcs = atoi(argv[2]);

    norm = 1./mcs;
    //string file = argv[6];
    int counter = 0;

    Ising model(n, temp);
    model.MonteCarlo(mcs);



    double E = model.average[0]*norm/pow(n,2);
    double M = model.average[4]*norm/pow(n,2);
    double E2 = model.average[1]*norm/pow(n,4);
    double M2 = model.average[3]*norm/pow(n,4);

    double Cv = (E2 - E*E)/pow(temp,2);
    double X = (M2 - M*M)/temp;

    cout << "T = " << temp << endl;
    cout << "<E> = " << E << endl;
    cout << "<M> = " << M << endl;
    cout << "E^2 = " << E2 << endl;
    cout << "M^2 = " << M2 << endl;
    cout << "Cv = " << Cv << endl;
    cout << "X = " << X << endl;

    cout << "analytic E = " << analyticE(temp) << endl;
    cout << "analytic M = " << analyticM(temp) << endl;

    /*

    vector<double> CV;
    vector<double> X;
    vector<double> temperature;
    vector<double> Evariance;
    vector<double> Mvariance;
    vector<double> M;
    vector<double> E;

    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp, false);
        model.MonteCarlo(mcs);


        E.push_back(model.average[0]*norm);
        M.push_back(model.average[2]*norm);
        CV.push_back(model.average[5]*norm/(temp*temp));
        X.push_back(model.average[6]*norm/temp);
        //Evariance.push_back(model.average[5]);
        //Mvariance.push_back(model.average[6]);
        temperature.push_back(temp);
        counter++;
        
    }

    vector<vector<double> > vec;
    vec.push_back(E);
    vec.push_back(M);
    //vec.push_back(Evariance);
    //vec.push_back(Mvariance);
    vec.push_back(CV);
    vec.push_back(X);
    vec.push_back(temperature);
    

    WriteToFile(vec, counter, file, n);

    */

    return 0;
}

double analyticE(double temp) {
    /*
    vector<int> E = {-8, 8, -8};
    double Z = 0;
    double sum = 0;
    for (int i = 0; i < E.size(); i++) {
        Z = (4*cosh(8/temp) + 12);
        sum += (1./Z)*E[i]*exp(-E[i]/temp);
    }
    */
   double Z = (4*cosh(8/temp) + 12);
   double sum = (-32*sinh(8/temp)/Z);

    return sum;
}

double analyticM(double temp) {
    vector<int> E = {-8, 0, 8, 0, 0, -8};
    vector<int> M = {4, 2, 0, 0, 2, 4};
    double Z = 0;
    double sum = 0;
    for (int i = 0; i < E.size(); i++) {
        Z = (4*cosh(8/temp) + 12);
        sum += (1./Z)*M[i]*exp(-E[i]/temp);
    }

    return sum;
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
        //myfile << ",";
        //myfile << vec[5][j];
        //myfile << ",";
        //myfile << vec[6][j];
        myfile << endl;
    }
    myfile.close();
}