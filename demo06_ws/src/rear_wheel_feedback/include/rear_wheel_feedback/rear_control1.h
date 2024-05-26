#ifndef REAR_CONTROL_1_
#define REAR_CONTROL_1_

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
/*
这个control1 就算单纯的重新写了下这个计算的方法

*/
#define PI 3.1415926
using namespace std;
class RearControlFeedback1
{

    private:
        double Kpsi, K2, L;
    public:

    RearControlFeedback1(double Kpsi,double K2, double L);

    static double normalizeAngle(double angle);


    double rearWheelFeedbackControl(vector<double>robot_state, double e, double k, double ref_psi);

    
};






#endif