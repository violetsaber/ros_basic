#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "demo01_action/AddIntsAction.h"

/*  
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
        4.创建action客户端对象;
        5.发送目标，处理反馈以及最终结果;
        6.spin().

*/
//完成任务的时候返回
void done_cb(const actionlib::SimpleClientGoalState &state, const demo01_action::AddIntsResultConstPtr &result)
{
    //响应成功的
    /* state  状态的反馈 */
    if(state.state_ == state.SUCCEEDED) //如果响应成功了
    {
        ROS_INFO("响应成功 %d",result->result);
    }
    else
    {

        ROS_INFO("响应失败");
    }
}
//激活的时候反馈
void ac_fb()
{
    ROS_INFO("客户段 与 服务段的连接 建立了");
}
//连续反馈的 回调 这个就算feedback 连续反馈的值
void feedback_cb(const demo01_action::AddIntsFeedbackConstPtr &feedback)
{
    //激活后的连续的反馈 
    ROS_INFO("连续的反馈值 %f",feedback->progress_bar);
}
int main(int argc, char* argv[])

{   
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"addInts_client");
    ros::NodeHandle nh;
    /*
    SimpleActionClient(ros::NodeHandle &n, 
    const std::string &name, 话题名字
    bool spin_thread 默认是 true
    )
    */
    actionlib::SimpleActionClient<demo01_action::AddIntsAction> client(nh,"addInts");
    //判断 server是否开启 等待server  serer启动挂起
    ROS_INFO("等待服务器启动...");
    client.waitForServer();
    /*void sendGoal(const demo01_action::AddIntsGoal &goal, 设置目标值
    3个回调函数 
    done cb active cb 以及 feedback cb  结束的回调函数  激活时的callback 以及 持续返回返回值时候的callback
    boost::function<void (const actionlib::SimpleClientGoalState &state, const demo01_action::AddIntsResultConstPtr &result)> done_cb, 
    boost::function<void ()> active_cb, 
    boost::function<void (const demo01_action::AddIntsFeedbackConstPtr &feedback)> feedback_cb)
    Sends a goal to the ActionServer, and also registers callbacks If a previous goal is already active when this is called. We simply forget about that goal and start tracking the new goal. No cancel requests are made.*/
    
    demo01_action::AddIntsGoal goal;
    goal.num = 100;
    
    client.sendGoal(goal, &done_cb, &ac_fb, &feedback_cb);
    ros::spin();
    return 0;
}