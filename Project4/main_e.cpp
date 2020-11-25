#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <armadillo>
#include <ctime>

#include "isingmodel.hpp"

void WriteMCToFile(Ising& obj3, Ising& obj4, string filename, int mcs, int n);

int main(int argc, char *argv[]) {

        int mcs = atoi(argv[1]);
        int n = atoi(argv[2]);
        double low = 1;
        double high = 2.4;
        double norm = 1./mcs;

        clock_t begin = clock();

        Ising model3(n, low);
        Ising model4(n, high);
 
        model3.MonteCarlo(mcs, true);
        model4.MonteCarlo(mcs, true);

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "time taken = " << elapsed_secs << endl;

        WriteMCToFile(model3, model4, "prob.csv", mcs, n);

    return 0;
}

void WriteMCToFile(Ising& obj3, Ising& obj4, string filename, int mcs, int n) {

    ofstream myfile;
    myfile.open(filename);
    
    int rest;
    
    if(obj3.num_E < obj4.num_E)
    {
        myfile << "T=2.4, T=1.0" << endl;
        for (int i = 0; i < obj3.num_E; i++) 
        {
            myfile << obj4.count_de[i];
            myfile << ",";
            myfile << obj3.count_de[i];
            myfile << endl;
        }
        rest = obj4.num_E - obj3.num_E;

        for(int i = rest; i < obj4.num_E; i++)
        {
            myfile << obj4.count_de[i];
            myfile << endl;
        }

    }else
    {   
        myfile << "T=1.0, T=2.4" << endl;
        for (int i = 0; i < obj4.num_E; i++) 
        {
            myfile << obj3.count_de[i];
            myfile << ",";
            myfile << obj4.count_de[i];
            myfile << endl;
        } 
        
        rest = obj3.num_E - obj4.num_E;

        for(int i = rest; i < obj3.num_E; i++)
        {
            myfile << obj3.count_de[i];
            myfile << endl;
        }

    }

    myfile.close();
    

}