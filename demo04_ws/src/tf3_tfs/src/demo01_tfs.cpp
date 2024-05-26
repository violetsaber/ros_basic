#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_ros/buffer.h"
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
#include"geometry_msgs/TransformStamped.h"
/*
计算son1和son2的相对关系
计算son1在son2的坐标值
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
    //设置坐标点
    geometry_msgs::PointStamped point_s1;
    point_s1.header.frame_id ="son1";
    point_s1.header.stamp = ros::Time::now();
    point_s1.point.x = 1;
    point_s1.point.y = 2;
    point_s1.point.z = 3; 
    while(ros::ok())
    {

        rate.sleep();
        try
        {
            //计算son1 son2的关系
            // target的坐标系 源坐标系 以及 时间批评 time(0.0)就算最近的一个时间 一个取值 计算相对关系
            
            geometry_msgs::TransformStamped  son1_To_son2 = buffer.lookupTransform("son2","son1",ros::Time(0.0));
            //
            ROS_INFO("son1 相对于son2的关系 父级 %s  子级  %s  %.2f  %.2f %.2f", son1_To_son2.header.frame_id.c_str(), 
                    son1_To_son2.child_frame_id.c_str(),
                    son1_To_son2.transform.translation.x,
                    son1_To_son2.transform.translation.y,
                    son1_To_son2.transform.translation.z);


            //计算son1点在son2的坐标系的位置
            //被转换的坐标点 在son2
            geometry_msgs::PointStamped  point_s1_ats2 = buffer.transform(point_s1,"son2");
            ROS_INFO("son1的点在son2的值 %.2f  %2.f  %.2f",point_s1_ats2.point.x, 
                                        point_s1_ats2.point.y ,
                                        point_s1_ats2.point.z);
                                        /*3   2    3*/
        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误提示%s",e.what());
            std::cerr << e.what() << '\n';
        }
        
    }





    return 0;
}