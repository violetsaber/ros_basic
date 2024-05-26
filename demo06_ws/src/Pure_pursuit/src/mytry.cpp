#include"ros/ros.h"
#include"Kinematic_package/KinematicModel.h"
#include"Kinematic_package/mul_remap.h"

#include"eigen3/Eigen/Dense"
#include<cmath>
#include <algorithm>
#include"matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace std;
void f1()
{

    /*
    绘图
    */
   vector<vector<double>>refer_path(1000,vector<double>(2));
    vector<double>refer_x,refer_y; //保存参考数据用于画图
    // 生成参考轨迹
    for(int i=0;i<1000;i++){
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
//        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    }
    std::cout<<" 1 x"<<std::endl;
    plt::plot(refer_x, refer_y);
    plt::show();

}
int main(int argc , char* argv[])
{


    KinematicModel ugv(0,-1,0.5,2,2,0.1);
    say_hello();
    f1();
    return 0;
}