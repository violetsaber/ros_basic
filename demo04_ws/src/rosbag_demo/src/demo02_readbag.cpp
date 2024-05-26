#include"ros/ros.h"
#include"rosbag/bag.h"
#include"std_msgs/String.h"
#include"rosbag/view.h"
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "read_bag");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("hello.bag",rosbag::BagMode::Read);
    //读取数据  
    //rosbag::View(bag);//有实现迭代器,可以直接for循环
    //读取消息的集合
    for(auto &&m: rosbag::View(bag))//rosbag::MessageInstance
    {
        //m的类型 rosbag::MessageInstance
        //get有topic data 时间 数据等
        std::string topic = m.getTopic();//返回的是string类型
        ros::Time time = m.getTime();//返回的是string类型
        std_msgs::String::ConstPtr p = m.instantiate<std_msgs::String>();//一个string的指针  string 的数据 msg文件是 用data 这个看 最开始的msg文件可以看到
        ROS_INFO("内容  %s, %.2f , %s ",topic.c_str(),time.toSec(),p->data.c_str());
    }

    bag.close();
    return 0;
}