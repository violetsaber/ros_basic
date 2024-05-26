#include"ros/ros.h"
#include"std_msgs/String.h"
#include"plumbing_pub_sub_doublemsg/pose1.h"

#include"plumbing_pub_sub_doublemsg/pose2.h"

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"msgpub");
    ros::NodeHandle nh;
    // 那个作用域下的 文件 是这个include 是 plumbing_pub_sub作用 羽 下的Person
    ros::Publisher pub=nh.advertise<plumbing_pub_sub_doublemsg::pose2>("newmsg",10);

    //声明自己建立的msg文件 之后给他付初值
    plumbing_pub_sub_doublemsg::pose2 p2;
    p2.vel.x=1.0;
    p2.vel.y=1.0;
    p2.vel.z=1.0;
    p2.ang.x=1.0;
    p2.ang.y=1.0;
    p2.ang.z=1.0;
    ros::Rate rate(1);
    ros::Duration(3.0).sleep();//创建后暂停3s
    while(ros::ok())
    {
        pub.publish(p2);
        //休眠 实现发布的频率
        rate.sleep();
        //修改发布的数据
        p2.vel.x+=1.0;
        //建议写上这个是处理回调函数的
        ros::spinOnce();

    }

    return 0;
}