#include"ros/ros.h"
#include<iostream>
#include"Kinematic_package/KinematicModel.h"
#include"matplotlibcpp.h"
#include"rear_wheel2/myreference2.h"
namespace  plt = matplotlibcpp;

void f1()
{

    double x0 = 0.0, y0=-1.0,psi = 0.5,v=2,L=2,dt=0.1;
    KinematicModel ugv(x0,y0,psi,v,L,dt); 
    std::cout<<"运动学模型"<<std::endl;
    plt::show();
}

void f2()
{
    vector<vector<double>>refer_path(1000,vector<double>(2));
    vector<double>refer_x,refer_y; //保存参考数据用于画图
    // 生成参考轨迹
    for(int i=0;i<1000;i++)
    {
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0)+2.5*cos(refer_path[i][0]/2.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
//        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    }
    plt::plot(refer_x,refer_y,"b--");
    plt::show();

}
void f3()
{
    double dt=0.1; // 时间间隔，单位：s
    double L=2; // 车辆轴距，单位：m
    double v = 2; // 初始速度
    double x_0=0; // 初始x
    double y_0=-3; //初始y
    double psi_0=0; // 初始航向角
    KinematicModel ugv(x_0,y_0,psi_0,v,L,dt);
    
    vector<double>robot_state;
    robot_state = ugv.getState();
    MyReferencePath referencePath;
    vector<double>one_trial = referencePath.calcTrackError(robot_state);
    


}
void f4()
{
    
}

int main(int argc, char* argv[])
{
    // f1();
    // f2();
    f3();
    return 0;
}