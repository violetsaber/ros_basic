#include"ros/ros.h"
#include<iostream>
#include"Kinematic_package/KinematicModel.h"
#include"matplotlibcpp.h"
#include"util_reference/uti_my_reference.h"
#include<eigen3/Eigen/Dense>
namespace plt = matplotlibcpp;

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
void f4()
{
    MatrixXd A(3,2), B(2,3);
    A<<1,1,
    1,1,
    1,1;
    B<<2,2,2,
    2,2,2;
    MatrixXd C = A *B;
    cout<< C <<endl;

}
void f3()
{
    MyReference referpath;
    for(int i=0 ; i<referpath.refer_path.size(); i++)
    {
        referpath.refer_x[i] = referpath.refer_path[i][0];
        referpath.refer_y[i] = referpath.refer_path[i][1];
    }
    plt::plot(referpath.refer_x,referpath.refer_y,"b--");
    plt::show();
}
int main( int argc, char* argv[])
{
    // f1();
    // f2();
    f3();
    f4();
    return 0;
}