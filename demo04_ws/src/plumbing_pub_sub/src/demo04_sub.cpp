#include"ros/ros.h"
#include"plumbing_pub_sub/Person.h"



/*
订阅实现
*/
//使用msg的常量指针 对比 std_msgs的 string的写法 
// std_msg::String::ConstPtr  这个东西的引用 &msg  
//最重要前面还需要const
void donewMsg(const plumbing_pub_sub::Person ::ConstPtr &msg)
{
    ROS_INFO("订阅的信息： 人的名字：%s , 人的年龄： %d, 人的身高: %.2f", msg->name.c_str(),msg->age,msg->height);
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    
    ros::init(argc,argv,"newmsg_sub");
    ROS_INFO("this is a subscriber");
    ros::NodeHandle nh;
    //话题名称  队列长度  回调函数
    ros::Subscriber sub=nh.subscribe("newmsg",10,donewMsg);
    ros::spin();//每次到这个地方 都去执行回调函数
    return 0;
}