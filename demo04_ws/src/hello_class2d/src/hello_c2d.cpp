#include"ros/ros.h"
#include"hello_class2d/hello_c2d.h"
//头文件是功能包 名字加上头文件将 之后放在include/功能包下面 因此我们也要这样引用
namespace hello_cpp{


void myhello::run()
{
    ROS_INFO("run a divie class cpp");
}

}