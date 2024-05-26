#include"ros/ros.h"
#include"std_msgs/String.h"
#include"sstream"
int main(int argc,char *argv[])
{

    setlocale(LC_ALL, "");
    ros::init(argc,argv,"apub");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<std_msgs::String>("fang",10);
    
    ros::Rate rate(10);
    int num=0;
    //创建后待机
    ros::Duration(3.0).sleep();
    while(ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss<<"hello world"<<num;

        msg.data=ss.str();
        pub.publish(msg);
        num++;
        rate.sleep();
        ros::spinOnce();//处理发布的回调函数 
        ROS_INFO("Hello world DEMO04");
    }
    return 0;

} 