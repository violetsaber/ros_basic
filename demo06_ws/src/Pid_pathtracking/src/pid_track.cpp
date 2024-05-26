#include"ros/ros.h"
#include"eigen3/Eigen/Dense"
#include"Pid_pathtracking/KinematicModel.h"
#include"Pid_pathtracking/PID_controller.h"
#include"Pid_pathtracking/Myreference.h"
#include<vector>

#include<cmath>
#include <algorithm>
#include"matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace std;

/**
 * 得到距离参考轨迹最近点的下标
 * @param robot_state 机器人状态（x,y）
 * @param refer_path 参考路径
 * @return 距离参考轨迹最近点的下标
 */
double calTargetIndex(vector<double>robot_state, vector<vector<double>>refer_path){
    vector<double>dists;
    for (vector<double>xy:refer_path) {
        double dist = sqrt(pow(xy[0]-robot_state[0],2)+pow(xy[1]-robot_state[1],2));
        dists.push_back(dist);
    }
    return min_element(dists.begin(),dists.end())-dists.begin(); //返回vector最小元素的下标
}
//调试代码
void ki()
{
    
    //这个是是试一下 运动学模型
    KinematicModel knmodel(1,2,3,4,5,6);
    vector<double> a = knmodel.getState();
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"a"<<std::endl;
    // 输出的结果 是   1 2 3 4 a
    

}
//调试代码
void f2()
{
    // 设置kp ki kd target upper lower的值
    PID_controller pid_controller(1.0, 1.0 , 1.0,1.0,2.0,1.0);
    double u = pid_controller.calOutput(0.0);
    std::cout<<"value  " << u<< std::endl;
}

void delta_pid()
{
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
    KinematicModel ugv(0,-1,0.5,2,2,0.1);
    std::cout<<" ugv x"<<std::endl;
    PID_controller_delta PID(2,0.01,30,0.,PI/6,-PI/6);
    vector<double>x_,y_;
    //机器人状态
    vector<double>robot_state(2);
    std::cout<<" robot_state x"<<std::endl;
    for(int i=0;i<500;i++)
    {
        plt::clf();
        robot_state[0]=ugv.x;
        robot_state[1]=ugv.y;
        double min_ind = calTargetIndex(robot_state,refer_path);
        double alpha = atan2(refer_path[min_ind][1]-robot_state[1], refer_path[min_ind][0]-robot_state[0]);
        double l_d = sqrt(pow(refer_path[min_ind][0]-robot_state[0],2)+pow(refer_path[min_ind][1]-robot_state[1],2));
        double theta_e = alpha-ugv.psi;
        
        double e_y = -l_d*sin(theta_e);
        double delta_f = PID.calOutput(e_y);
        //std::cout<< delta_f<<std::endl;
        ugv.updateState(0,delta_f);
        x_.push_back(ugv.x);
        y_.push_back(ugv.y);
        //cout<<ugv.x<<","<<ugv.y<<refer_path[min_ind][0]<<","<<refer_path[min_ind][1]<<endl;
      
        /*
        plt::plot(refer_x,refer_y,"b--");
        plt::plot(x_, y_,"r");
        plt::grid(true);
        plt::ylim(-2.5,2.5);
        plt::pause(0.01);*/
    }   
    const char* filename = "./pic_save/delta_pid_demo.png";
    cout << "Saving result to " << filename << std::endl;
    
    plt::plot(refer_x,refer_y,"b--");
    plt::plot(x_, y_,"r");
    plt::grid(true);
    plt::ylim(-2.5,2.5);
    //plt::pause(0.01);
    plt::save(filename);
    plt::show();
}
void basic_pid()
{
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
    plt::save("./pic_save/pid basic.png");
    KinematicModel ugv(0,-1,0.5,2,2,0.1);
    std::cout<<" ugv x"<<std::endl;
    PID_controller PID(2,0.01,30,0.,PI/6,-PI/6);
    //保存机器人（小车）运动过程中的轨迹
    vector<double>x_,y_;
    //机器人状态
    vector<double>robot_state(2);
    std::cout<<" robot_state x"<<std::endl;
    for(int i=0;i<500;i++)
    {
        plt::clf();
        robot_state[0]=ugv.x;
        robot_state[1]=ugv.y;
        double min_ind = calTargetIndex(robot_state,refer_path);
        double alpha = atan2(refer_path[min_ind][1]-robot_state[1], refer_path[min_ind][0]-robot_state[0]);
        double l_d = sqrt(pow(refer_path[min_ind][0]-robot_state[0],2)+pow(refer_path[min_ind][1]-robot_state[1],2));
        double theta_e = alpha-ugv.psi;
        
        double e_y = -l_d*sin(theta_e);
        double delta_f = PID.calOutput(e_y);
        //std::cout<< delta_f<<std::endl;
        ugv.updateState(0,delta_f);
        x_.push_back(ugv.x);
        y_.push_back(ugv.y);
        //cout<<ugv.x<<","<<ugv.y<<refer_path[min_ind][0]<<","<<refer_path[min_ind][1]<<endl;
      
        /*
        plt::plot(refer_x,refer_y,"b--");
        plt::plot(x_, y_,"r");
        plt::grid(true);
        plt::ylim(-2.5,2.5);
        plt::pause(0.01);*/
    }   
    const char* filename = "./pic_save/pid_demo.png";
    cout << "Saving result to " << filename << std::endl;
    
    plt::plot(refer_x,refer_y,"b--");
    plt::plot(x_, y_,"r");
    plt::grid(true);
    plt::ylim(-2.5,2.5);
    //plt::pause(0.01);
    plt::save(filename);
    plt::show();
    
}

//如果想让实现的代码在调试后面实现 先声明 再去实现
int main(int argc,char* argv[])
{
    
    

    //basic_pid();
    delta_pid();
    
    return 0;
}