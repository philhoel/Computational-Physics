#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>
#include <ctime>

#include "isingmodel.hpp"

void WriteMCToFile(Ising& obj, Ising& obj2, Ising& obj3, Ising& obj4, string filename, int mcs, int n);

int main(int argc, char *argv[]) {

        int mcs = atoi(argv[1]);
        int n = atoi(argv[2]);
        double low = 1;
        double high = 2.4;
        double norm = 1./mcs;

        clock_t begin = clock();

        Ising model(n, low);
        Ising model2(n, high);
        Ising model3(n, low, false);
        Ising model4(n, high, false);
        model.MonteCarlo(mcs, true);
        model2.MonteCarlo(mcs, true);
        model3.MonteCarlo(mcs, true);
        model4.MonteCarlo(mcs, true);

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "time taken = " << elapsed_secs << endl;

        WriteMCToFile(model, model2, model3, model4, "MCvalues.csv", mcs, n);

    return 0;
}

void WriteMCToFile(Ising& obj, Ising& obj2, Ising& obj3, Ising& obj4, string filename, int mcs, int n) {

    ofstream myfile;
    myfile.open(filename);
    myfile << "EO_low, EO_high, EU_low, EU_high, MO_low, MO_high, MU_low, MU_high, EOl_accept_config, EOh_accept_config, EUl_accept_config, EUH_accept_config" << endl;
    for (int i = 0; i < mcs; i++) {
        myfile << obj.Eave[i]/pow(n,2);
        myfile << ",";
        myfile << obj2.Eave[i]/pow(n,2);
        myfile << ",";
        myfile << obj3.Eave[i]/pow(n,2);
        myfile << ",";
        myfile << obj4.Eave[i]/pow(n,2);
        myfile << ",";
        myfile << obj.Mave[i]/pow(n,2);
        myfile << ",";
        myfile << obj2.Mave[i]/pow(n,2);
        myfile << ",";
        myfile << obj3.Mave[i]/pow(n,2);
        myfile << ",";
        myfile << obj4.Mave[i]/pow(n,2);
        myfile << ",";
        myfile << obj.accept[i];
        myfile << ",";
        myfile << obj2.accept[i];
        myfile << ",";
        myfile << obj3.accept[i];
        myfile << ",";
        myfile << obj4.accept[i];
        myfile << endl;
    }

}