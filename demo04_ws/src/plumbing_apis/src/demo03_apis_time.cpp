#include"ros/ros.h"

void cv(const ros::TimerEvent& event)
{
//传人一个时间变量 实参 const不改变值在callback内
    //时间的事件
    ROS_INFO("--------------");
    ROS_INFO("调用当前时间%f",event.current_real.toSec());
}
int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"tostime");
    ros::NodeHandle nh;//没有这一部 就没有时间初始化的
    ros::Time time_now = ros::Time ::now(); //Time是一个类 将当前时间封装近来 返回 now被执行的时刻 参考1970 1 .1 0时间0s
    //   ros的参考时间 东八区是8.00 整数

    /*
   [ INFO] [1711718558.758684409]: 当前时间 1711718558.76
    */
    ROS_INFO("当前时间 %.2f",time_now.toSec());//ti_Sec变为秒 
    

   
    /*
  
    [ INFO] [1711718558.759021661]: 当前时间 1711718558
    
    */
    ROS_INFO("当前时间 %d",time_now.sec);//转换为整形的结果
    /*TIME 还有nsec的操作 */
    //一个是设置秒和 毫秒  3123454678毫秒
    ros::Time  t11(20,3123454678);//距离ros定义的表在时间的数量
    ROS_INFO("当前时间 秒和毫秒%.3f",t11.toSec());//ti_Sec变为秒 
    //直接设置一个浮点数的内容
    ros::Time  t1(20.3123454678);//距离ros定义的表在时间的数量
    /*
    [ INFO] [1711718558.759036111]: 当前时间 20.312
    */
    ROS_INFO("当前时间 浮点数 %.3f",t1.toSec());//ti_Sec变为秒 

    //持续时间
    //接受 int double float类型的数据
    ros::Time st = ros::Time ::now(); 
    ROS_INFO("开始休眠 浮点数  st  = %.3f",st.toSec());//ti_Sec变为秒 
    ros::Duration du(4.5);
    du.sleep();//休4.5s
    ros::Time sted = ros::Time ::now(); 
    ROS_INFO("休眠结束 浮点数  sted = %.3f",sted.toSec());//ti_Sec变为秒 

    //时间加法
    //时刻 与持续时间的加法和减法
    ros::Time st1 = ros::Time::now();
    ROS_INFO("开始 ros::Time st1 = ros::Time::now(); %.3f",st1.toSec());//ti_Sec变为秒 
    ros::Duration du2(4);
    ros::Time st2 = ros::Time::now();
    
    ros::Time duuu2 = st1 + du2;
    ros::Time duuu = st1 - du2;//start时间减去4秒的结果 时刻与持续时间的计算
    ROS_INFO("结束 ros::Time duuu = st1 - du2 %.3f",duuu.toSec());//ti_Sec变为秒 
    ROS_INFO("结束 ros::Time duuu = st1 + du2 %.3f",duuu2.toSec());//ti_Sec变为秒 

    // 时刻与时刻之间的运算
    //ros::Time sum_time= st1 +st2;//不可以+运算 只是可以减法
    ros::Duration sum_time = st- sted;
    ROS_INFO("结束 ros::Duration sum_time = st- sted;; %.3f",sum_time.toSec());//ti_Sec变为秒 
    
    //持续时间的运算
    // ros::Duration du2(4);    ros::Duration sum_time = st- sted;
    ros::Duration du3 = du2-sum_time;  
    ROS_INFO("ros::Duration du3 = du2-sum_time;   %.3f",du3.toSec());//ti_Sec变为秒 
    ros::Duration du4 =  du2+ sum_time;
    ROS_INFO("ros::Duration du3 = du2 + sum_time;   %.3f",du4.toSec());//ti_Sec变为秒 
    ros::Duration du44 =  du- sum_time;
    ROS_INFO("ros::Duration du44 =  du-  sum_time;  %.3f",du44.toSec());//ti_Sec变为秒 

    // ros::Rate rate(10); 10hz
    // 使用定时器实现rate(10) 10hz的处理数据
    ROS_INFO("-------分割----------");
    /*
    nh.createTimer的传入参数说明
    
    传入ros::Duration 时间间隔
    const ros::TimeCallback &callback  回调函数 封装执行的任务
    bool oneshot = false   是不是一次性的定时器 true 隔1s后，就会运行一次，但是运行一次就结束了
    bool autostart = true  
    */
   

    //这个是 基础两个参数的使用
    //ros::Timer time1=nh.createTimer(ros::Duration(1), cv);//每隔开1秒输出一个cv中的信息

    // 只运行一次   oneshot的使用 用的时候 最好把其他的注释调
    //ros::Timer time1=nh.createTimer(ros::Duration(1), cv,true);//每隔开1秒输出一个cv中的信息  ，家了true后就只运行一次了
    
    
    // 这个是只运行一次 而且不自己启动 用我们的time1.start();让我们自己选择什么时候 启动
    //ros::Timer time1=nh.createTimer(ros::Duration(1), cv,true,false);//
    //ROS_INFO("-------Timer 启动----------");
    //time1.start();
    // 这个是修改了 回调函数的例子， 这个回调函数的例子，是和传入的参数 的中种类不相关的，就是需要我去查一下，这个类型的数据 里面都有什么成员函数
    ros::Timer time1=nh.createTimer(ros::Duration(1), cv,false,true);//

    ros::spin();
    return 0;
}