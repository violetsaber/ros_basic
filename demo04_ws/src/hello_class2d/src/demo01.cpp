#include"ros/ros.h"
#include"hello_class2d/hello_c2d.h"

int main(int argc, char *argv[])

{

    ros::init(argc,argv,"class_hello_desperate");
    hello_cpp::myhello obj;
    obj.run();
    return 0;
}