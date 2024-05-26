#include"ros/ros.h"
#include"Kinematic_package/KinematicModel.h"
#include"Pure_pursuit/puresuit.h"
#include"matplotlibcpp.h"

#define Pi 3.1415926
namespace plt =matplotlibcpp;

int main(int argc,char* argv[])
{

    double x0 = 0.0, y0=-1.0,psi = 0.5,v=2,L=2,dt=0.1;
    double lam = 0.1; // 前视距离系数
    double c=2; // 前视距离
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

    // 运动学模型
    KinematicModel ugv(x0,y0,psi,v,L,dt); 
    vector<double> x_, y_;
    vector<double> robot_state(2);//初始化 2个大小
    PurePursuit pureControl;
    for( int i=0; i<500;i++)
    {

        plt::clf();
        robot_state[0]=ugv.x;
        robot_state[1]=ugv.y;
        //参考博客中的公式
        //前视距离
        double l_d = lam*ugv.v+c;

        double min_ind = pureControl.calTargetIndex(robot_state, refer_path, l_d);
        double delta = pureControl.purePursuitControl(robot_state, refer_path[min_ind], l_d, ugv.psi, L);
        ugv.updateState(0,delta);
        x_.push_back(ugv.x);
        y_.push_back(ugv.y);

        //画图
        plt::plot(refer_x,refer_y,"b--");
        plt::plot(x_, y_,"r");
        plt::grid(true);
        plt::ylim(-5,5);
        plt::pause(0.01);

    }
    const char* filename = "./pic_save/pureControl.png";
    cout << "Saving result to " << filename << std::endl;
    plt::save(filename);
    //plt::show();

    return 0;
}