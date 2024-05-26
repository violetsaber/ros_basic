#ifndef PURESUIT_QINGHUAN
#define PURESUIT_QINGHUAN
#include<iostream>
#include"ros/ros.h"
#include<vector>
#include<cmath>
#include <algorithm>

// vector 不用std 无法直接使用vector std::vector using namespace std; vector 就可以了
class PurePursuit
{
    public:
    //车辆的当前位置点  给一个所有的轨迹，我们基于车辆当前位置，有一个前视距离，在中国前视距离内，寻找一个refer path的点 最远的点
    // robot state是车辆的状态 refer_path 参考轨迹 n个点  每个点是3个状态 是 x , y , psi 航向角
    double calTargetIndex(std::vector<double>robot_state, std::vector<std::vector<double> >refer_path, double l_d);

    //纯跟踪的方法 车辆的当前状态 我们的目标点， 计算我们的 前轮角度 
    double purePursuitControl(std::vector<double>robot_state, std::vector<double>current_ref_point,double l_d, double psi, double L);

};







#endif 