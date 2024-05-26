#include"ros/ros.h"
#include"turtlesim/Pose.h"
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"

//声明变量接受传入的参数
std::string turtle_name;


void domsg(const turtlesim::Pose ::ConstPtr& pose)
{
    //活得位置信息，转化成坐标西相对关系  静态在cpp文件只是生成一次 之后多次调用
    // 这是static的特性  每次使用都是一个 没有static 每次调用回调函数 都会新生成一个
    //
    static  tf2_ros::TransformBroadcaster pub;
    geometry_msgs::TransformStamped ts;
    ts.header.stamp = ros::Time::now();
    //世界坐标系
    ts.header.frame_id = "world";
    //乌龟的坐标系
    //ts.child_frame_id = "turtle1";

    ts.child_frame_id = turtle_name ;
    ts.transform.translation.x = pose->x;//乌龟的坐标系  x就是乌龟的坐标系
    ts.transform.translation.y = pose->y;//乌龟的坐标系
    ts.transform.translation.z = 0;
    //通过theta x和y轴是没有旋转的 乌龟是绕着z周旋转的

    //位置信息是2d的 但是有个偏航校 没有俯仰和翻滚较度
    //欧拉较是0，0，theta
    /* ts.transform.rotation.x = 0;
    ts.transform.rotation.y = 0;
    ts.transform.rotation.z = pose->theta; */
    //发布数据
    tf2::Quaternion qtn;
    //通过欧拉较自动设置寺四元数字
    qtn.setRPY(0,0,pose->theta);
    //设置四元数
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();
    //发布数据
    pub.sendTransform(ts);
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    /*
    发布方 需要订阅乌龟的为子信息，转化成相对于窗体的坐标 关系
        准备： 订阅乌龟的话题 乌龟的pose这个msg的信息
        x,y,z  linear_velociy,angular_velocity   全是float类型 这个是2维度 直接就算这两个信息
        
    */
    /*解析 laucnh 文件 args传入的参数 */
    std::cout<<"***********************"<<std::endl;//这里是看一下如果ros::init初始化前 这个argv都是什么
    std::cout<<argv[0]<<std::endl;
    std::cout<<argv[1]<<std::endl;
    std::cout<<argv[2]<<std::endl;
    std::cout<<argv[3]<<std::endl;
    ros::init(argc, argv, "dynamic_pub");
    
    ros::NodeHandle nh;
    //topic 是turtlepose
    /*
    修改订阅的话题名称 turtle1 动态传入的 frame_id也是动态传入的
    */
   //放在初始化函数句柄的后面就是2个 
   if (argc!=2)
    {

        //功能包名 和一个参数 
        ROS_INFO("清传入一个参数,%d",argc);
        return 1;
    }
    else
    {
        turtle_name = argv[1];
        std::cout<<turtle_name<<std::endl;

    }
    ros::Subscriber sub=nh.subscribe(turtle_name+"/pose",10,domsg);
    ros::spin();
    return 0;
    

}