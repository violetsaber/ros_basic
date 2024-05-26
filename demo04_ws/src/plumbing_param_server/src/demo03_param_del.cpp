#include "ros/ros.h"


int main(int argc, char* argv[])
{

    ros::init(argc,argv,"delparamNode");
    ros::NodeHandle nh;
    bool flag1 = nh.deleteParam("radius");
    if (flag1)
    {
        ROS_INFO("param deleted");
    }
    else{
        ROS_INFO("param not deleted");
    }
    //ros::param的实现
    bool flag2 = ros::param::del("radius_param");
    if (flag2)
    {
        ROS_INFO("param deleted radius_param");
    }
    else
    {
        ROS_INFO("param not deleted");
    }
    return 0;
}