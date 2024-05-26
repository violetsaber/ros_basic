#include"ros/ros.h"
#include"std_msgs/String.h"
int main(int argc, char* argv[])
{
    
    /*
    argc, argv name 可选参数 options

    name是节点的名字  ros 中不允许重名的操作 

    argc是功能包 + rosrun plumbing_apis_pub demo01 中  dmeio01 +后面传入的实参  在这个demo01 我们是可以传入参数

    argc 是 int 等于 功能包的别名 + 后面传入参数的个数    实参个数 + 1

    argv 是一个char 的数组   这些实参被封入了 argv中 rosrun plumbing_apis_pub demo01_apis_pub  _length:=10  向param中传入了一个 length 一个10 在param空间中

    options 是一个节点启用选项  设置参数
    节点名称不能 相同  同时启动报错
    如果一个节点需要启动两次，回报错
    如何让一个节点启动两次正常运行

    */
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"apis_pub",ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    /*
    针对静态数据  只需要发布一次就ok了 将latch 这个可选参数设在为True  
    */
    ros::Publisher pub=nh.advertise<std_msgs::String>("fang",10,true);
    
    ros::Rate rate(10);
    int num=0;
    //创建后待机
    ros::Duration(3.0).sleep();
    while(ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss<<"hello world"<<num;

        msg.data=ss.str();
        if (num<10)
        {
            //test new 这里作的变更 主要三我们就发送这个数据几次 之后在发布万数据后 看看 能不能用
            pub.publish(msg);
            ROS_INFO("我发布的信息是:%s", msg.data.c_str());
        }
                
        
        num++;
        rate.sleep();
        pub.publish(msg);
        ros::spinOnce();//处理发布的回调函数 
        ROS_INFO("一轮回调执行完毕");
        if(num>15)
        {
            ROS_INFO("shutdown");
            ros::shutdown();
        }
    }

    return 0;
}