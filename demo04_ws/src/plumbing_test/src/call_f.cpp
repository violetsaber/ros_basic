#include"plumbing_test/call_f.h"
#include"ros/ros.h"
namespace callback_f
{

void cc_f::run(const turtlesim::Pose::ConstPtr& pose)
{
    ROS_INFO("class 位置信息包含 %2.f,%2.f, 朝向 %2.f,速度 %2.f,%2.f",pose->x,pose->y,pose->theta,pose->linear_velocity,pose->angular_velocity);
}
}