#include"Pid_pathtracking/PID_controller.h"


PID_controller::PID_controller(double kp, double ki, double kd, double target,  double upper, double lower):kp(kp),ki(ki),kd(kd),target(target),upper(upper),lower(lower)
{
    /*
    PID的构造函数，设定比例系数、积分系数、微分系数 目标值  上下限
    */
}
void PID_controller::setTarget(double target)
{
    PID_controller::target = target;

}

void PID_controller::setK(double kp, double ki, double kd)
{
    this->kd = kd;
    this->ki = ki;
    this->kp = kp;
}
void PID_controller::setBound(double upper, double lower)
{
    this->upper = upper ;
    this->lower = lower ;
}

double PID_controller::calOutput(double state)
{
    /*
    kp 比例 根据当前误差计算结果
    ki 累积误差值 计算
    kd 两次误差的差值计算
    */
    this->error = target - state ;
    double u = this->error * this->kp + this->ki * this->sum_error + this->kd * (this->error - this->pre_error);
    if (u > this->upper)
    {
        u = this->upper;
    }
    if (u < this->lower)
    {
        u = this ->lower;
    }
    this->pre_error = this->error;
    this->sum_error += this->error;
    return u;
}

void PID_controller::reset()
{
    this->error = 0.0;
    this->pre_error =0.0;
    this->sum_error = 0.0;

}
void PID_controller::setSumError(double sum_error)
{
    this->sum_error = sum_error;
}




PID_controller_delta::PID_controller_delta(double kp, double ki, double kd, double target, double upper, double lower,double inc):kp(kp),ki(ki),kd(kd),target(target),upper(upper),lower(lower),inc(inc)
{
    /*
    设置 增量式 PID的计算方法 
    kp, ki, kd, target, upper, lower, inc;
    inc是上一次控制量的变化值 初始值是0，我们不对初始的u作变化
    */
}

void PID_controller_delta::setTarget(double target)
{

    this->target = target;
}
void PID_controller_delta::setK(double kp, double ki, double kd)
{
    this->kd = kd;
    this->ki = ki;
    this->kp = kp;
}

void PID_controller_delta::setBound(double upper, double lower)
{
    this->upper = upper;
    this->lower = lower;
}
void PID_controller_delta::updaterror()
{
    this->ll_error = this->pre_error;
    this->pre_error = this->error;
    /*
    能够正常输出
    */
    // std::cout<<"update_error"<<std::endl;
}

double PID_controller_delta::calOutput(double state)
{
    /*
    state 是double 横向误差 最后计算 可以是横向与纵向的解耦 
    */
    this->error = this->target -state;
    double delta_u = this->kp * (this->error - this->pre_error) + this->ki * this->error + this->kd * (this->error- 2 * this->pre_error + this->ll_error);
    /*
    调用class的其余成员函数 强调是当前对象的 成员函数
    this-> 前缀是可选的，因为编译器通常可以根据上下文推断出变量是成员变量还是局部变量。但是，使用 this-> 可以提高代码的可读性，尤其是在变量名可能与局部变量或参数名冲突的情况下。
    */
    this->updaterror();
    this->inc = this->inc + delta_u;
    if (this->inc > this->upper)
    {
        this->inc = this->upper;
    }
    if (this->inc < this->lower)
    {
        this->inc = this->lower;
    }
    return this->inc;

}
void PID_controller_delta::reset()
{
    this->pre_error = 0.0;
    this->ll_error =0.0;
}
void PID_controller_delta::setSumError(double ll_error)
{
    this->ll_error = ll_error;
}
void PID_controller_delta::setinc(double inc)

{
    this->inc = inc ;
}
