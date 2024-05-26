/*
roscpp rospy std_msgs rosbag
*/
/*
rosbag 向磁盘写入数据 
1、有话题
2、有消息
3、消息是字符串类型的

*/
#include"ros/ros.h"
#include"rosbag/bag.h"
#include"std_msgs/String.h"
int main(int argc, char* argv[])
{
    ros::init(argc,argv,"rosbag_write");
    ros::NodeHandle nh;
    //bag对象
    rosbag::Bag bag;
    // 打开文件流动  文件名称，操作方式    write read appned 写 读 追加
    bag.open("hello.bag",rosbag::BagMode::Write);
    //话题名称 时间 消息
    std_msgs::String msg;
    msg.data =  "hello_xxx";
    bag.write("/chatter", ros::Time::now() , msg);
    bag.write("/chatter", ros::Time::now() , msg);
    bag.write("/chatter", ros::Time::now() , msg);
    bag.write("/chatter", ros::Time::now() , msg);
    //关闭
    bag.close();
    return 0;
}