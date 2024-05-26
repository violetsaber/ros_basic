#include"ros/ros.h"
#include"std_msgs/String.h"


int main(int argc, char*argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv,"hello");
    ros::NodeHandle nh;
    //全局话题
    //ros::Publisher pub = nh.advertise<std_msgs::String>("/chatter",1000);
    //ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chatter",1000);
    //相对命名空间 
    //ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
    //ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chatter",1000);
    ros::NodeHandle nh1("~");
    //ros::Publisher pub = nh1.advertise<std_msgs::String>("chatter",1000);
    ros::Publisher pub = nh1.advertise<std_msgs::String>("yyy/chatter",1000);
    ROS_INFO("全局");
    while(ros::ok())
    {

    }

    return 0;
}