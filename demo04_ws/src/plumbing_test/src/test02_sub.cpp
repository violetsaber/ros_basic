#include"ros/ros.h"
#include"turtlesim/Pose.h"
#include"plumbing_test/call_f.h"
void dopose(const turtlesim::Pose::ConstPtr& pose)
{

    ROS_INFO("位置信息包含 %2.f,%2.f, 朝向 %2.f,速度 %2.f,%2.f",pose->x,pose->y,pose->theta,pose->linear_velocity,pose->angular_velocity);
}

int main(int argc, char* argv[])

{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "sub_pose");
    ros::NodeHandle nh;
    callback_f::cc_f obj;
    ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,&callback_f::cc_f::run, &obj);
    ros::spin();

    return 0;
}