#include"ros/ros.h"
#include"plumbing_head_src/hello.h"

int main(int argc,char* argv[])
{

    setlocale(LC_ALL, "");
    ros::init(argc,argv,"helloheadsrc");
    hello_ns::myhello obj;
    obj.run();//需要把class文件与use_hello cpp关联
}