#include"ros/ros.h"
#include"demo01_action/AddIntsAction.h"//在devel文件夹下的 
/*一个服务对象*/
#include"actionlib/server/simple_action_server.h"

/*  
服务段 计算从1到N的累加 产出连续反馈  累加后的最后结果
    需求:
        创建两个ROS节点，服务器和客户端，

        客户端可以向服务器发送目标数据N（一个整型数据）

        服务器会计算1到N之间所有整数的和，这是一个循环累加的过程，返回给客户端，
        这是基于请求响应模式的，
        又已知服务器从接收到请求到产生响应是一个耗时操作，每累加一次耗时0.1s，
        为了良好的用户体验，需要服务器在计算过程中，
        每累加一次，就给客户端响应一次百分比格式的执行进度，使用action实现。

    流程:
        1.包含头文件;
        2.初始化ROS节点;
        3.创建NodeHandle;
        4.创建action服务对象;
        5.处理请求,产生反馈与响应;
        6.spin().

*/


typedef actionlib::SimpleActionServer<demo01_action::AddIntsAction> Server;

void callback(const demo01_action::AddIntsGoalConstPtr& goalPtr, Server* server)
{
    //处理 数据
    int num  = goalPtr->num;
    ROS_INFO("客户端的目标值 %d", num);
    //返回连续数据
    ros::Rate rate(10);
    int result =0;
    demo01_action::AddIntsFeedback fb;
    for ( int i = 0; i < num; i++)
    {
        result +=1;
        rate.sleep();
        //
//  参数类型是feedback
// void publishFeedback(const demo01_action::AddIntsFeedback &feedback)
        
        fb.progress_bar = i / float(num);
        server -> publishFeedback(fb);
    }
    //最终结果
    /* void setSucceeded(const demo01_action::AddIntsResult &result = actionlib::SimpleActionServer<demo01_action::AddIntsAction>::Result(), const std::string &text = ((std::string)(""))) */
    //我们这个函数  是要一个返回值是 demo01_action::AddIntsResult的一个数据  这个数据是 等价的
    demo01_action::AddIntsResult r;
    r.result = result;
    server -> setSucceeded(r);
}


class AddIntsActionServer

{

protected:

    // Action服务器的回调函数

    void executeCB(const demo01_action::AddIntsGoalConstPtr& goalPtr)

    {
    int num  = goalPtr->num;
    ROS_INFO("客户端的目标值 %d", num);
    //返回连续数据
    ros::Rate rate(10);
    int result =0;
    demo01_action::AddIntsFeedback fb;
    for ( int i = 0; i < num; i++)
    {
        result +=1;
        rate.sleep();
        //
//  参数类型是feedback
// void publishFeedback(const demo01_action::AddIntsFeedback &feedback)
        
        fb.progress_bar = i / float(num);
        as_.publishFeedback(fb);
    }
    //最终结果
    /* void setSucceeded(const demo01_action::AddIntsResult &result = actionlib::SimpleActionServer<demo01_action::AddIntsAction>::Result(), const std::string &text = ((std::string)(""))) */
    //我们这个函数  是要一个返回值是 demo01_action::AddIntsResult的一个数据  这个数据是 等价的
    demo01_action::AddIntsResult r;
    r.result = result;
    as_.setSucceeded(r);

    }


public:

    AddIntsActionServer(std::string name) : 

        as_(nh_, name, boost::bind(&AddIntsActionServer::executeCB, this, _1), false)

    {

        as_.start();

    }


private:

    ros::NodeHandle nh_;

    actionlib::SimpleActionServer<demo01_action::AddIntsAction> as_;

};
int main( int argc ,char* argv[])

{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"action_server_addints");
    ros::NodeHandle nh;
    /* SimpleActionServer(ros::NodeHandle n, 话题句柄
    std::string name,  actuon的name 话题名字 topic
    boost::function<void (const demo01_action::AddIntsGoalConstPtr &)> execute_callback,  回调函数 无返回值  参数 const demo01_action::AddIntsGoalConstPtr &
    bool auto_start)是否自动启动 
     */
    //_1是占位用的 就算 直接传进去 这个server数据对象
    // Server server( nh,"addInts", boost::bind(&callback,_1, &server), false) ;
    // server.start();
    AddIntsActionServer server("addInts");
    
    ros::spin();
    return 0;
}