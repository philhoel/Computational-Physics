#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>
#include <mpi.h>

#include "isingmodel.hpp"

void WriteToFile(vector<vector<double> >& vec, int counter, string filename);

int main(int argc, char *argv[]) {
    int team = MPI_Init (&argc, &argv);

    int num_threads, my_rank;
    
    
    team = MPI_Comm_size (MPI_COMM_WORLD, &num_threads);
    team = MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

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
    vector<double> Cv;
    vector<double> X;

    /*
    if(my_rank==0)
    {
        double t1, t2; 
        t1 = MPI_Wtime();     
    }*/
    for (double temp = initial_temp; temp <= final_temp; temp += temp_step) {

        Ising model(n, temp);
        model.MonteCarloMPI(mcs, team);
        
        if(my_rank==0)
        {    
            E.push_back(model.average[0]*norm/pow(n,2));
            E2.push_back(model.average[1]*norm/pow(n,4));
            M.push_back(model.average[2]*norm/pow(n,2));
            M2.push_back(model.average[3]*norm/pow(n,4));
            Mabs.push_back(model.average[4]*norm/pow(n,2));
            temperature.push_back(temp);

            //cout << "myrank " << my_rank << " " << "EAVE = " << model.average[0]/pow(n,2) << endl;
            cout << "temp =  " << temp << endl;

            double Evar, Mvar;
            Evar = (E2[counter]-E[counter]*E[counter]);
            Mvar = (M2[counter]-Mabs[counter]*Mabs[counter]);


            Cv.push_back(Evar/pow(temp,2));
            X.push_back(Mvar/temp);

            counter++;
        }
        
    }
    /*
    if(my_rank==0)
    {
        t2 = MPI_Wtime();
        cout << "time taken = " << t2-t1 << endl;
    }
    */

    vector<vector<double> > vec;
    if(my_rank==0)
    {
        vec.push_back(E);
        vec.push_back(M);
        vec.push_back(Mabs);
        vec.push_back(Cv);
        vec.push_back(X);
        vec.push_back(temperature);

        WriteToFile(vec, counter, file);
    }
    team = MPI_Finalize();
    return 0;
}

void WriteToFile(vector<vector<double> >& vec, int counter, string filename) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "E, M, Mabs, Cv, X, Temp" << endl;
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