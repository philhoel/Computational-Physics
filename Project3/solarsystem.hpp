#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

struct CelestBody {

    string name;
    double mass;

    mat pos;
    mat vel;
    mat acc;

    vec kin;
    vec pot;

    mat p;
    mat L;

    CelestBody(string Name, double Mass, int n);

    void initialValues(double x, double y, double z, double vx, double vy, double vz);

    void initialValues(double x, double y, double z);

};

class SolarSystem {

    private:

        int n;
        int size;

        double T;
        double h;

        double g;

        vector<CelestBody> CB;

    public:

        const double PI = 3.141592653589793238463;

        SolarSystem(int N, double Time);

        void addBody(string name, double mass, vec initial);

        void addSun(string name, double mass, vec initial);

        double gravitation(int SP, int cnt, vec r_vec_cnt, int axis);

        void massCenter();

        void verlet();

        void euler();

        void writeValuesToFile(string filename);

        void writePlotInfo(string filename);

        vector<CelestBody> getList();

        int getN();


};