#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>

class System {

    public:

        double initial_temp, final_temp, temp_step;

        int n, mcs, counter;

        string filename;

        double norm;

        mat ave;

        System(int N, int MCS, double i_temp, double f_temp, double t_step, string fname);

        System(int N, int MCS, string fname);

        void tempChange();

        void MCtemp(double low, double high);

        //void constTemp(double low, double high);

        void WriteToFile(vector<vector<double> >& vec);

        void WriteMCToFile();

        //void WriteMCToFile(Ising& obj, Ising& obj2, Ising& obj3, Ising& obj4);


};