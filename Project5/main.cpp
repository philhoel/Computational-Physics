#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <time.h>

#include "Solver.hpp"
#include "Solver2dim.hpp"

using namespace std;
using namespace arma;


int main(int argc, char * argv[]) {
    
    int problem = atoi(argv[1]);
    int n = atoi(argv[2]);
    int time = atoi(argv[3]);
    double dt = atof(argv[4]);

    // n, time and dt gets adjusted for forward euler


    if (problem == 1) {

        Solver obj(n/1000, time*100, dt/100);
        obj.ForwardEuler();
        obj.WriteToFile("FE.csv");

        Solver obj2(n, time, dt);
        obj2.BackwardEuler();
        obj2.WriteToFile("BE.csv");

        Solver obj3(n, time, dt);
        obj3.CrankNicholson();
        obj3.WriteToFile("CN.csv");

    } else if (problem == 2) {

        Solver obj(200, 1000, 0.00001);
        obj.ForwardEuler();
        obj.AnalyticExpression();
        obj.WriteToFile("FE.csv");
        obj.WriteToFile("anal.csv", true);

        Solver obj2(n, time, dt);
        obj2.BackwardEuler();
        obj2.WriteToFile("BE.csv");

        Solver obj3(n, time, dt);
        obj3.CrankNicholson();
        obj3.WriteToFile("CN.csv");

        Solver obj4(n, time, dt);
        obj4.AnalyticExpression();
        obj4.WriteToFile("anal2.csv", true);

    } else if (problem == 3) {

        Solver2dim obj2D(n, time, dt);
        obj2D.ForwardEuler(1000, 10000, 50000, 100000);
        obj2D.WriteToMultipleFiles("2DEuler_t1.csv", "2DEuler_t2.csv", "2DEuler_t3.csv", "2DEuler_t4.csv");

    } else if (problem == 4) {

        clock_t start, finish;
        double runtime[100][3];
        //runtime = double[100][3];

        for (int i = 0; i < 100; i++) {

            Solver obj(n, time, dt);
            start = clock();
            obj.ForwardEuler();
            finish = clock();

            runtime[i][0] = (double)(finish - start)/(CLOCKS_PER_SEC);

            Solver obj2(n, time, dt);
            start = clock();
            obj2.BackwardEuler();
            finish = clock();

            runtime[i][1] = (double)(finish - start)/(CLOCKS_PER_SEC);

            Solver obj3(n, time, dt);
            start = clock();
            obj3.CrankNicholson();
            finish = clock();

            runtime[i][2] = (double)(finish - start)/(CLOCKS_PER_SEC);

        }

        double FE_sum, BE_sum, CN_sum;
        FE_sum = BE_sum = CN_sum = 0;

        for (int i = 0; i < 100; i++) {
            FE_sum += runtime[i][0]/100;
            BE_sum += runtime[i][1]/100;
            CN_sum += runtime[i][2]/100;
        }

        cout << "Runtime FE: " << FE_sum << endl;
        cout << "Runtime BE: " << BE_sum << endl;
        cout << "Runtime CN: " << CN_sum << endl;
        
    }

    return 0;

}