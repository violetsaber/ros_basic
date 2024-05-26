#include"ros/ros.h"
#include"Kinematic_package/KinematicModel.h"
#include"Kinematic_package/mul_remap.h"
int main(int argc , char* argv[])
{


    KinematicModel ugv(0,-1,0.5,2,2,0.1);
    std::cout<<"C1"<<std::endl;
    say_hello();
    
    return 0;
}