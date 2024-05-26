#include<iostream>
#include"rear_wheel_feedback/rear_control.h"
#include"Kinematic_package/KinematicModel.h"
#include"matplotlibcpp.h"
#include"rear_wheel_feedback/rear_my_reference.h"

namespace plt = matplotlibcpp;

#define PI 3.1415926

int main(int argc, char* argv[])
{
    double Kpsi = 3.0 , K2=1.5; //李亚普诺夫判距
    double dt =0.1;
    double L =2;
    double v =2.0;
    double x_0 = 0.0;
    double y_0 = 3.0;
    double psi_0 = 0.0;


    

    vector<double> x_, y_;
    MyReferencePath referencePath;
    KinematicModel ugv(x_0, y_0, psi_0, v, L, dt);

    RearWheelFeedback rwf(Kpsi, K2, L);
    vector<double> robot_state;
    for(int i = 0 ; i<500; i++)
    {
        plt::clf();
        robot_state=ugv.getState();
        vector<double> one_trial = referencePath.calcTrackError(robot_state);
        // {error,k,yaw,min_index};
        double e = one_trial[0] , k = one_trial[1], ref_psi = one_trial[2];
        double delta = rwf.rearWheelFeedbackControl(robot_state, e, k, ref_psi);
        ugv.updateState(0,delta);
        x_.push_back(ugv.x);
        y_.push_back(ugv.y);
        
        
        //画图
        
    }
    // save figure
    
    plt::grid(true);
    plt::ylim(-5,5);
    plt::plot(x_, y_,"r");
    plt::plot(referencePath.refer_x,referencePath.refer_y,"b--");
    plt::pause(0.01);
    const char* filename = "./pic_save/rear_demo.png";
    cout << "Saving result to " << filename << std::endl;
    plt::save(filename);
    plt::show();










    return 0;
}