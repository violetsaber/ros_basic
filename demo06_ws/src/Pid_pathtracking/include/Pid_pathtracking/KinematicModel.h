#ifndef  KINEMATIC_MODEL
#define KINEMATIC_MODEL


#include <iostream>
#include <vector>
#include <cmath>
#include"eigen3/Eigen/Dense"
using namespace std;
using namespace Eigen;

#define PI 3.1415926
class KinematicModel
{
    public:
    /*
    自行车模型
    后轴中心 为质心和参考点
    前轮转向
    车辆的x y psi 车辆的横摆角 v是速度
    L是车辆的轴距 前后轮的轴距
    dt 是运动学模型的更新时间
    */
    double x,y,psi,v,L,dt;
    public:
    KinematicModel();
    KinematicModel(double x, double y, double psi, double v, double l, double dt);
    vector<double>getState();
    void updateState(double accel, double delta_f);
    vector<MatrixXd>stateSpace(double ref_data, double ref_yaw);
    

};
#endif