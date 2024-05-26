#include"ros/ros.h"



int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "lognode");
    ros::NodeHandle nh;
    //日志输出
    ROS_DEBUG("调试信息不打印控制台");
    ROS_INFO("一般信息");
    ROS_WARN("警告信息黄色");
    ROS_ERROR("错误信息红色");
    ROS_FATAL("致命错误 红色");

    return 0;
}