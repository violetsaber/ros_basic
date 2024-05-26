#include"ros/ros.h"
#include"Pure_pursuit/puresuit.h"


double PurePursuit::calTargetIndex(std::vector<double>robot_state, std::vector<std::vector<double> >refer_path,  double l_d)
{
    /*
    robot_state 是车辆的状态 就是 x,y,psi 纵向坐标， 横向坐标， 航向较
    refer_path  参考轨迹， 给的n个轨迹点， 每个轨迹点是 x,y,psi 轨迹点
    l_d 前视距离  我们在这个距离内，找一个refer_path合适的距离
    */
    std::vector<double> dists;
    for(std::vector<double> xy : refer_path)
    {
        //sqrt(pow(xy[0]-robot_state[0],2)+pow(xy[1]-robot_state[1],2));
        double distance = sqrt( pow(xy[0]-robot_state[0],2)+ pow(xy[1] - robot_state[1], 2) );
        dists.push_back(distance);
        /* sqrt(pow(xy[0]-robot_state[0],2)+pow(xy[1]-robot_state[1],2)); */
    }
    // 给出指定的范围  vector 的范围
    double min_id =  min_element(dists.begin(),dists.end())-dists.begin();

    double delta_l = sqrt(pow(robot_state[0] - refer_path[min_id][0],2) + pow(robot_state[1] - refer_path[min_id][1], 2) );
    while (l_d > delta_l && min_id < refer_path.size()-1)
    {
        //在前视距离中 我们找最远的那个点跑
        min_id+=1;
        delta_l = sqrt( pow(robot_state[0] - refer_path[min_id][0] , 2 ) + pow(robot_state[1] - refer_path[min_id][1], 2) );
    }

    return min_id;
}

double PurePursuit::purePursuitControl(std::vector<double> robot_state, std::vector<double> current_ref, double l_d, double psi, double L)
{
    // 这个必须是 目标点-车辆点  否则会影响alpha的正负性能
    double alpha = atan2(   current_ref[1] - robot_state[1] ,  current_ref[0] - robot_state[0] ) - psi;

    double delta = atan2( 2 * L  * sin(alpha), l_d);
    return delta;


}