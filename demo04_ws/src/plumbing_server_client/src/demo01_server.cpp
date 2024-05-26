#include"ros/ros.h"
#include"std_msgs/String.h"
#include"plumbing_server_client/AddInts.h"
/*
+
服务器实现
包含头文件
初始化节点 
创建服务器对象
处理响应文件

*/
bool doNums(plumbing_server_client::AddInts::Request& request,plumbing_server_client::AddInts::Response& response)
{

    /*
    有请求对象 和 addints下的request类型  plumbing_server_client::AddInts::Request& request
    响应对象   plumbing_server_client::AddInts::Response& response
    
    
    */
    //从请求中把数据拿出来
    /*
    处理请求
    组织响应
    */

    //处理请求
    int num1 = request.num1;
    int num2 = request.num2 ;
    ROS_INFO("收到的请求数据 num1 =%d,  num2=%d", num1, num2);
    int sum = num1 + num2;
    response.sum = sum;
    ROS_INFO("求和的结果是 sum = %d", sum);

    return true;
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    
    ros::init(argc,argv,"newserver1");
    ros::NodeHandle nh;
    // 船舰 serviceserver对象 我们需要 一个话题名字   一个是  回调函数 处理请求  数据类型自动推导
    ros::ServiceServer server=nh.advertiseService("addInts",doNums);
    ROS_INFO("服务器端启动");
    ros::spin();
    return 0;
}