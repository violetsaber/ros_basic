#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"//订阅对象

#include"tf2_ros/buffer.h"//订阅对象 把 订阅数据缓存到这里
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;
    //创建订阅文件
    tf2_ros::Buffer buffer;//把数据存到这里
    //订阅对象， 对象存在到buff里
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";
    ps.header.stamp = ros::Time::now();

    ps.point.x=2.0;
    ps.point.y=3.0;
    ps.point.z=5.0;
    //转换坐标系的算法 tf的内置实现  通过循环转化数据 将从雷达坐标系的障碍物数据变换为 基于车辆坐标系的数据
    ros::Rate rate(10);
    //两个坐标系的转化需要时间，因此在这里设置了个时间
    //ros::Duration(2).sleep();
    while(ros::ok())
    {

        rate.sleep();
        //转换成 baselink的座标点 buffer有个函数transform
        //我们将ps这个从laser坐标 变换到 base_link 发布是 发布了两个关系   
        try
        {
            geometry_msgs::PointStamped ps_out=buffer.transform(ps,"base_link");
             ROS_INFO("转换后的数据:(%.2f,%.2f,%.2f ),参考的坐标系是: %s",ps_out.point.x, ps_out.point.y, ps_out.point.z,  ps_out.header.frame_id.c_str());
        }
        
        //我们
        //[ INFO] [1712280321.756704367]: 转换后的数据:(2.00,3.00,5.00 ),参考的坐标系是: laser
        catch(const std::exception &e)
        {
           ROS_INFO("异常信息 %s",e.what());
           std::cout<<"error: "<<e.what()<<std::endl;

        }
        ros::spinOnce();
    }
    return 0;
}