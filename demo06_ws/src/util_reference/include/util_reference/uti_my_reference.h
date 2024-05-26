#ifndef MY_REFRENCE_SIN_COS
#define MY_REFRENCE_SIN_COS



#include<iostream>
#include<cmath>
#include<vector>
#include"eigen3/Eigen/Dense"

#include<algorithm>
using namespace std;
using namespace Eigen;
#define PI 3.1415926
struct refTraj {
    MatrixXd xref, dref;
    int ind;
};

struct parameters {
    int L;
    int NX, NU, T;
    double dt;
};

class MyReference
{
    public:
        vector<double> refer_x, refer_y;
        vector<vector<double>> refer_path;
    public:
        MyReference();
        vector<double> calcTrackError(vector<double> robot_state);
        double normalizeAngle( double angle);
        refTraj calc_ref_trajectory(vector<double> robot_state, parameters param, double dl = 1.0);



};







#endif






