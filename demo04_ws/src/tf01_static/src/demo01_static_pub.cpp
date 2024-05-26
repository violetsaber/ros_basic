#include"ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"
int main(int argc, char*argv[])
{
/* 
发布坐标系的相对关系
1、包含头文件
2、初始化操作 
3、创建发布对象
4、组织发布数据
5、发布数据
6、spin()
*/
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_pub");
    ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;
    geometry_msgs::TransformStamped tfs;
    tfs.header.seq = 100;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link";//坐标系关系 被参考的
    tfs.child_frame_id="laser";

    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;

    tf2::Quaternion qtn;//创建四元数对象
    //设置欧拉角度  将欧拉较变为四元数
    //翻滚值 俯仰 偏航值
    qtn.setRPY(0,0,0);//单位是弧度
    tfs.transform.rotation.x =qtn.getX();
    tfs.transform.rotation.y =qtn.getY();  
    tfs.transform.rotation.z =qtn.getZ();
    tfs.transform.rotation.w =qtn.getW();
    pub.sendTransform(tfs);
    ros::spin();
    return 0;
}