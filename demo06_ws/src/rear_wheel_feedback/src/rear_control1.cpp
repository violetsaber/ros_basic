#include"rear_wheel_feedback/rear_control1.h"



double RearControlFeedback1::normalizeAngle(double angle)
{

    while (angle>PI)
    {
        angle-=2*PI;
    }
    while(angle<-PI)
    {
        angle+=2*PI;
    }
    return angle;
}   
RearControlFeedback1::RearControlFeedback1(double Kpsi, double K2, double  L):Kpsi(Kpsi),K2(K2),L(L){};

double RearControlFeedback1::rearWheelFeedbackControl(vector<double> robot_state, double e, double k, double ref_psi)
{
    double psi = robot_state[2], v = robot_state[3];
    double psi_e = this->normalizeAngle(psi - ref_psi);
    double psi_dot = v * k * cos(psi_e) / (1.0 - k * e) - K2 * v * sin(psi_e) * e / psi_e - Kpsi * abs(v) * psi_e ;
    // double psi_dot = v * k * cos(psi_e) / (1.0 - k * e) - K2 * v * sin(psi_e) * e / psi_e - Kpsi * abs(v) * psi_e ;
    if (psi_e == 0.0 || psi_dot ==0.0)
    {
        return 0;
    }
    double delta = atan2(psi_dot * L , v);

    return 0;
}