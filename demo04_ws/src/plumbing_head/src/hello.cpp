#include"ros/ros.h"
#include"plumbing_head/hello.h"//include 下哪个文件家的 头文件
namespace hello_ns
{

void myhello::run()
{
    ROS_INFO("run函数执行");
}
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hellomyclass");
    hello_ns::myhello obj;
    obj.run();

    return 0;
}