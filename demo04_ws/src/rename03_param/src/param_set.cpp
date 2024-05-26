#include"ros/ros.h"

int main(int argc, char* argv[])
{




    ros::init(argc,argv,"setparam");
    ros::param::set("/paramA",52);
    ros::param::set("paramB",1);
    ros::param::set("~paramC",1);
    ros::NodeHandle nh;
    nh.setParam("setparamA",1);
    nh.setParam("setparamB",1);
    ros::NodeHandle nh1("~");
    nh1.setParam("setparamC",1);
    return 0;
}