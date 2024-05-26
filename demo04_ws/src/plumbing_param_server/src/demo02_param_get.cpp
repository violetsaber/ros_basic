#include"ros/ros.h"

/*

查询实现
ros::NodeHandle

ros::param


param(键,默认值) 
            存在，返回对应结果，否则返回默认值

        getParam(键,存储结果的变量)
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamCached键,存储结果的变量)--提高变量获取效率
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamNames(std::vector<std::string>)
            获取所有的键,并存储在参数 vector 中 

        hasParam(键)
            是否包含某个键，存在返回 true，否则返回 false

        searchParam(参数1，参数2)
            搜索键，参数1是被搜索的键，参数2存储搜索结果的变量
ros::param
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    ros::init(argc,argv,"param_get111");
    ros::NodeHandle nh;
    double radius = nh.param("radius",0.5);
    ROS_INFO("radius = %f",radius);
    //查询键值 为radius的 没有就算0.51
    
    //保留几位小数 
    
    //查询键值 为radius的 存在就算0.51
    double radius2=0.2;
    bool result = nh.getParam("radius",radius2);
    
    if(result)
    {
        ROS_INFO("radius1 = %f",radius2);
    }
    else
    {
        ROS_INFO("失败");
        ROS_INFO("失败  radius1 = %f",radius2);

    }
    double radius3=0.0;
    ROS_INFO("nh.getParamCached 只是性能有提升 肉眼无法观察");
    bool result1 = nh.getParamCached("radius",radius3);
    if(result1)
    {
        ROS_INFO("radius1 = %f",radius3);
    }
    else
    {
        ROS_INFO("失败");
        ROS_INFO("失败  radius1 = %f",radius3);

    }
    //getParamNames
    std::vector<std::string> param_names;
    nh.getParamNames(param_names);
    //&a 是 给你一个真实的参数  但纯的for auto name : param_names 是形参  &&右值引用 是不复制 你给我直接移动过来
    //for(auto &name:param_names)
    //右值 引用
    for(auto &&name:param_names)
    {
        ROS_INFO("getParam :%s",name.c_str());
    }
    //hasParam 是否存在key
    bool flag1 = nh.hasParam("radius");
    bool flag2 = nh.hasParam("flag");
    ROS_INFO("key 存在吗%d",flag1);//返回值为1 代表true
    ROS_INFO("key 存在吗%d",flag2);//返回值为0 代表 false
    //searchParam 搜索 key
    std::string search_key ;
    //搜索的key radius  之后用search_key保存
    nh.searchParam("radius",search_key);
    ROS_INFO("搜索结果 key: %s",search_key.c_str());
   
    
    return 0;
}