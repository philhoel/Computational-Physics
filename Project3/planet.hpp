#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <string>

using namespace std;
using namespace arma;

class Planet {

    private:

        int n;
        double h;

        string name;
        double mass;
        double force;
        double r;
        

    public:

        mat pos;
        mat vel;
        mat acc;

        Planet(string Name, int N);
        
        void update_r(int i);

        double getForce();

        void setForce(double F);

};