#include"ros/ros.h"
#include"std_msgs/String.h"
#include"sstream"
//回调函数传入 订阅到的消息的常量指针引用
void doMsg(const std_msgs::String::ConstPtr &msg)
{
    ROS_INFO("订阅到的信息%s",msg->data.c_str());
}
int main(int argc,char *argv[])
{
    
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"asub");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe("fang",10,doMsg);
    
    ros::spin();
    
    return 0;

} 