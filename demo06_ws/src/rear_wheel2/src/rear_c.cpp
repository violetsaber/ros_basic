#include"rear_wheel2/rear_c.h"


RearWheelFeedback::RearWheelFeedback(double Kpsi, double K2 , double L):Kpsi(Kpsi),K2(K2),L(L)
{
    
}
double RearWheelFeedback::normalizeAngle(double angle)
{

    while (angle >PI)
    {
        angle-=2*PI;
    }
    while (angle <-PI)
    {
        angle+=2*PI;

    }
    return angle;
}

double RearWheelFeedback::rearWheelFeedbackControl(vector<double>robot_state, double e, double k,  double ref_psi)
{
    //航向角误差
    double psi = robot_state[2] , v = robot_state[3];
   
    double psi_e = this->normalizeAngle(psi - ref_psi);

    // 李亚普诺夫第二定律
    double psi_dot =  v * cos(psi_e) * k / (1.0 - k * e) - this->K2 * v  *sin(psi_e)/psi_e  * e -Kpsi * abs(v) * psi_e;
    if (psi_e == 0 || psi_dot == 0)
    {
        return 0;
    }
    double delta = atan2(L * psi_dot , v );

    return delta ;

}
vector<double> RearWheelFeedback::caltrackerror(vector<double> robot_state, vector<vector<double>> refer_path)

{
    double x = robot_state[0] , y = robot_state[1];
    vector<double> d_x( refer_path.size()) , d_y( refer_path.size() ) , d( refer_path.size());
    for (int i = 0 ;  i< refer_path.size(); i++)
    {
        d_x[i] = refer_path[i][0] - x;
        d_y[i] = refer_path[i][1] - y;
        d[i] = sqrt(d_x[i] * d_x[i] + d_y[i] * d_y[i]);
    }
    double min_index  = min_element( d.begin(), d.end() )  - d.begin();
    //refer_path 与x轴的夹角
    double yaw  = refer_path[min_index][2];
    //轨迹 s(t) = s(x,y) 随着时间变化的 的x和y  在frenet的坐标系 曲线的斜率
    double k = refer_path[min_index][3];

    double error = d[min_index];
    double angle  = normalizeAngle(yaw - atan2( d_y[min_index], d_x[min_index]));
    double fx = d_x[min_index] , fy =d_y[min_index];
    int flag1,flag2,flag3;
    double n1,n2,n3;
    n1 = sin(angle) * sin(normalizeAngle(yaw))  - cos(angle) * cos(normalizeAngle(yaw));
    if(n1>0)
    {
        flag1 = 1;
    }
    else
    {
        flag1 = -1;
    }

    n2 = -1 * fy * cos(normalizeAngle(yaw)) - (-1) * fx * sin(normalizeAngle(yaw));
    if(n2>0)
    {
        flag2 = 1;
    }
    else
    {
        flag2 = -1;
    }

    if (angle < 0) 
    {
        error*=-1;
        flag3 =-1;
    }
    else
    {
        flag3 = 1 ;
    }
    cout<<"rearc"<<endl;
    cout<<"flag1: " <<flag1<<"  flag2: " <<flag2<<"   flag3 "<<flag3<<endl;
    cout<<"n1: " <<n1<<"   n2: " <<n2<<"  n3 "<<angle<< "  error " <<error <<endl;
    return{error,k,yaw,min_index};
}