#include"ros/ros.h"
#include "dynamic_reconfigure/server.h"
#include "demo02_dr/drConfig.h"


 /*  
    动态参数服务端: 参数被修改时直接打印
    实现流程:
        1.包含头文件
        2.初始化 ros 节点
        3.创建服务器对象
        4.创建回调对象(使用回调函数，打印修改后的参数)
        5.服务器对象调用回调对象
        6.spin()
*/
void  cb( demo02_dr::drConfig &config, uint32_t level)
{
    
    ROS_INFO("动态参数 : init_param  $%d",config.int_param);
    ROS_INFO("动态参数 : init_param  $%.2f",config.double_param);
    ROS_INFO("动态参数 : init_param  $%s",config.string_param.c_str());
    ROS_INFO("动态参数 : init_param  $%d",config.bool_param);
    ROS_INFO("动态参数 : init_param  $%d",config.list_param);
    ROS_INFO("动态参数 -------------");
}

int main(int argc, char* argv[])
{


    setlocale(LC_ALL, "");
    ros::init(argc,argv,"dynamic_param");
    dynamic_reconfigure::Server<demo02_dr::drConfig> server;


    // void setCallback(const boost::function<void (demo02_dr::drConfig &, uint32_t level)> &callback)

    server.setCallback(boost::bind(&cb,_1,_2));


    ros::spin();







    return 0;
}