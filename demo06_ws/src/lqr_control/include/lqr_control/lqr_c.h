#ifndef LQR_CONTRTOL1
#define LQR_CONTRTOL1

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#define EPS 1.0e-4
using namespace std;
using namespace Eigen;

class LQRContronl
{
    private:
        int N;
    public:
        LQRContronl(int n);
        MatrixXd calRicatti(MatrixXd A, MatrixXd B, MatrixXd Q , MatrixXd R);
        double lqrControl(vector<double> robot_state, vector<vector<double>> refer_patj, double s0, MatrixXd A, MatrixXd B, MatrixXd Q, MatrixXd R);
        MatrixXd lqrControl1(vector<double> robot_state, vector<vector<double>> refer_patj, double s0, MatrixXd A, MatrixXd B, MatrixXd Q, MatrixXd R);

};






#endif