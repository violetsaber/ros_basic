#include"ros/ros.h"
#include"helloclass/hello_h.h"

namespace hello_ns{


    void hello_pub::run()
    {
        ROS_INFO("Hello");
    }
}

int main(int argc, char *argv[]) 
{
    ros::init(argc,argv,"hellonewnode");
    hello_ns::hello_pub obj;
    obj.run();

    return 0;
}
