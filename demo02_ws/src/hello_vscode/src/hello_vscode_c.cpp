#include"ros/ros.h"
// 修改了 cpp文件下 c++14变成了c++17
/*
"cppStandard": "c++17" 这一项
对应的是cppStandard

*/
int main(int argc,char *argv[])
{
    setlocale(LC_CTYPE, "zh_CN.utf8");
    ros::init(argc,argv,"hello");
    
    ROS_INFO("hahaha");
    ROS_INFO("你好scode");
    return 0;
}