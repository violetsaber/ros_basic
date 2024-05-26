#include"ros/ros.h"
#include"turtlesim/Spawn.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"service_client_call");
    ros::NodeHandle nh;
    ros::ServiceClient client=nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    srv.request.x = 1.0;
    srv.request.y = 4.0;
    srv.request.theta = 1.57;
    srv.request.name = "turtle2";
    

    client.waitForExistence();
    bool flag1 = client.call(srv);
    //发送数据 返回的一个bool 代表是否成功响应
   
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