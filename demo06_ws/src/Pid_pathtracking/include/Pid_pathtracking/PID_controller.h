#ifndef CHHROBOTICS_CPP_PID_CONTROLLER_H
#define CHHROBOTICS_CPP_PID_CONTROLLER_H

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;


class PID_controller
{
    private:
    double kp, ki, kd, target, upper, lower;
    double error=0.0, pre_error =0.0, sum_error = 0.0;
    public:
    PID_controller(double kp, double ki, double kd, double target, double upper, double lower);
    void setTarget(double target);
    void setK(double kp, double ki, double kd);
    void setBound(double upper, double lower);
    double calOutput(double state);
    void reset();
    void setSumError(double sum_error);


};
class PID_controller_delta
{
    private:
    double kp, ki, kd, target, upper, lower, inc;
    double error=0.0,pre_error=0.0,ll_error=0.0;
    public:
    PID_controller_delta(double kp, double ki, double kd, double target, double upper, double lower,double inc=0.0);
    void setTarget(double target);
    void setK(double kp, double ki, double kd);
    void setBound(double upper, double lower);
    double calOutput(double state);
    void reset();
    void setSumError(double ll_error);
    void updaterror();
    void setinc(double inc );

};




#endif