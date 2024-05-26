#ifndef REAR_C1_
#define REAR_C1_

#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#define PI 3.1415926
using std::vector;
using std::cout;
using std::endl;

class RearWheelFeedback
{
    private:
        double Kpsi , K2, L;
    public:
        RearWheelFeedback(double Kpsi, double K2, double L);
        static double normalizeAngle(double angle);
        double rearWheelFeedbackControl(vector<double> robot_state, double e, double k, double ref_psi);
        vector<double> caltrackerror(vector<double> robot_state, vector<vector<double>> refer_path);

};

#endif