#include"ros/ros.h"

int main(int argc, char* argv[])
{

    setlocale(LC_ALL, "");
    ros::init(argc, argv, "setbackgroundcolor");
    ros::NodeHandle nh("turtlesim");//这个相当于命名空间把前面的内容 加进去
    //使用ros::param 不要创建节点  /turtlesim/background_r key value = 0
    /*
    ros::param::set("/turtlesim/background_r",0);
    ros::param::set("/turtlesim/background_b",0);
    ros::param::set("/turtlesim/background_g",0);
    */
    nh.setParam("background_r",255);
    nh.setParam("background_g",255);
    nh.setParam("background_b",255);
    return 0;
}