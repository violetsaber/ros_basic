
#include"Pid_pathtracking/KinematicModel.h"


KinematicModel::KinematicModel(double x, double y, double psi, double v,double l, double dt):x(x),y(y),psi(psi),v(v),L(l),dt(dt)
{
    /*
    构造函数重载  ：赋值方法
    */
   std::cout<<x<<","<<y<<","<<psi<<","<<v<<","<<L<<","<<dt<<","<<std::endl;
}

void KinematicModel::updateState(double accel,double delta_f)
{
    this->x = this->x + this->v * cos(this->psi) * this->dt;
    this->y = this->y + this->v * sin(this->psi) *this->dt;
    //车辆的航向角 更新公式 psi 初始角度 
    this->psi = this->psi + this->v/this->L * tan(delta_f) * this->dt;
    this->v = this->v +accel * this->dt ;
}

vector<double>KinematicModel::getState()
{

    return {x,y,psi,v};
}

vector<MatrixXd> KinematicModel::stateSpace(double ref_delta, double ref_yaw)
{
    MatrixXd A(3,3),B(3,2);
    //初始化一个矩阵 x(k+1) = Ax(k) + Bu(k)
    A<<1.0,0.0,v*dt*sin(ref_yaw),
    0.0,1.0,v*dt*cos(ref_yaw),
    0.0,0.0,1.0;
    B<<dt*cos(ref_yaw),0,
    dt * sin(ref_yaw),0,
    dt * tan(ref_delta)/L,v*dt/(L * cos(ref_delta) * cos(ref_delta));
    return {A,B};
    
}


