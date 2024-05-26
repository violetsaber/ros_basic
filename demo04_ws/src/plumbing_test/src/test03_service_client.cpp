#include"ros/ros.h"
#include"turtlesim/Spawn.h"

//这里都是头文件
int main(int argc , char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "sercice_clientcall");
    ros::NodeHandle nh;
    ros::ServiceClient client= nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    srv.request.x=1.0;
    srv.request.y=4.0;
    srv.request.theta=1.57;//最大值是3.14 向右是-3.14 右转90
    srv.request.name="turtle2";//不能重复调用的原因 是名字是一样的 如果想要重复i调用 需要把 名字该了 每个
    client.waitForExistence();
    //发送数据 返回的一个bool 代表是否成功响应
    bool flag1 = client.call(srv);
    if (flag1)
    {
        ROS_INFO("响应成功 %s ", srv.response.name.c_str());//这个是通过命令行看到spwan的命名方式了
    }
    else
    {
        ROS_INFO("响应失败");
    }

    return 0;
}