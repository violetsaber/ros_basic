#include"ros/ros.h"
#include"plumbing_head_src/hello.h"

namespace hello_ns
{

void myhello::run()
{
    ROS_INFO("源文件的成员函数执行");//使用ros的文件需要把ros包含在内
}

}