#include"ros/ros.h"
#include"plumbing_server_client/AddInts.h"


int main(int argc, char *argv[])
{
    /*
    用argc和argv      实现参数的动态提交

    格式：运行这个节点 rosrun 报名 节点名称 和 12 34

    获取命令行的参数

    argc是参数的个数 传入的是客户端名称  + 12   34 一个名称两个 int类型的数字
    argv是个字符串
    
    */
    
    setlocale(LC_ALL, "");
    if (argc!=3)
    {
        ROS_INFO("提交参数的个数不对");
        return 1;
    }

    ros::init(argc, argv,"newclient1");
    //创建函数句柄
    ros::NodeHandle nh;
    //nh.serviceClient 创建客户
    ros::ServiceClient client= nh.serviceClient<plumbing_server_client::AddInts>("addInts");
    //声明数据
    plumbing_server_client::AddInts ai;
    // requests plumbing_server_client::AddInts::Request & req; 这个是我们的request调用的法那个法 我们需要调用这个参数
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);

    //向客户端发送数据之前  我们先 看server是否启动 没有启动则挂起
    /*
    client.waitForExistence();
    ros::service::waitForService("addInts"); 传的参数是被等待的 服务 或者说 是具体的节点   
    这两个函数都可以实现 对 通信的挂起
    */
    //client.waitForExistence();

    ros::service::waitForService("addInts");
    //提交数据
    bool flag = client.call(ai);
    //返回的num继续会封装在 ai中
    if(flag)
    {
        ROS_INFO("响应成功 %d", ai.response.sum);
  
    }
    else
    {
        ROS_INFO("响应失败");
    }


    return 0;
}