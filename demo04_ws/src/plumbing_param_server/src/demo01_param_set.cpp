#include"ros/ros.h"



/*
实现 参数的新增和修改
ros::NodeHandle
setParam()
ros::param
set()
都有这个setParam的方法
配置 
add_executable
target_link_libraries
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"serverparams11111");
    ros::NodeHandle nh;
    /*参数新增 ------------------------*/
    //nh 方案
    nh.setParam("type","xiaohuangche");
    nh.setParam("radius",0.12);//这里设置的参数类型是 float类型 最开始我设置成了 "“ string 类型的数据  所有无法返回 float类型的东西
    //ros::param
    //传入一个键 一个值 键要独立的
    //键值重复会覆盖
    ros::param::set("type_param", "xiaobai");
    ros::param::set("radius_param",0.15);

    ROS_INFO("参数设置成功");
    //已经存在的健 再次设置就算修改
    ros::param::set("radius_param",0.1211);


    return 0;
}