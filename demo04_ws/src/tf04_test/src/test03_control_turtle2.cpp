#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_ros/buffer.h"
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
#include"geometry_msgs/TransformStamped.h"
#include"geometry_msgs/Twist.h"

/*
把turtle1的坐标系 换算成turtle2 的坐标系下的位置关系 
计算turtle2的速度信息 角速度 并发布除去
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"tfs_pub");
    ros::NodeHandle nh;
    //创建订阅对象
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);
    //编写解析逻辑
    ros::Rate rate(10);
    ros::Publisher pub= nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);
    while(ros::ok())
    {

        rate.sleep();
        try
        {
            //计算son1 son2的关系
            // target的坐标系 源坐标系 以及 时间批评 time(0.0)就算最近的一个时间 一个取值 计算相对关系
            // 计算turtle1 在turtle2的坐标系的位置 turtle2是父坐标系 
            
            geometry_msgs::TransformStamped  son1_To_son2 = buffer.lookupTransform("turtle2","turtle1",ros::Time(0.0));
            //
            ROS_INFO("turtle1 相对于 turtle2 的关系 父级 %s  子级  %s  %.2f  %.2f %.2f", son1_To_son2.header.frame_id.c_str(), //turtle2
                    son1_To_son2.child_frame_id.c_str(),//turtle1
                    son1_To_son2.transform.translation.x,
                    son1_To_son2.transform.translation.y,
                    son1_To_son2.transform.translation.z);

            /*
            初始化的结果是1.55  ， -4.54  0.0
            */
            geometry_msgs::Twist twist;
            //2维度的乌龟 只有x的值 角速度
            // x = 系数 + 两个乌龟之间的距离  z是系数乘以反正切
            twist.linear.x = 0.5 * sqrt(  pow(son1_To_son2.transform.translation.x,2)   + pow(son1_To_son2.transform.translation.y,2 )          );
            twist.angular.z = 4 * atan2(son1_To_son2.transform.translation.y, son1_To_son2.transform.translation.x);
            pub.publish(twist);
        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误提示%s",e.what());
            std::cerr << e.what() << '\n';
        }
        
    }





    return 0;
}