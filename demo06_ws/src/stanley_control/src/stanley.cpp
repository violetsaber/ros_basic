#include"stanley_control/stanley.h"


Stanley::Stanley(double k):k(k)
{
    /* 
    初始化增益系数 这个系数 与速度相乘 
    得到我们的一个前视距离
    我们根据这个距离 去找 轨迹上的参考点
    
    */
}

double Stanley::calTargetIndex(std::vector<double> robot_state, std::vector< std::vector<double>> refer_path)
{
    /*
    robot_state 长度为4 的 vector.size() ==4
    refer_path(n， vector<double>(3)) x y psi
    */
    double  L=2;//车身的长度 要做修改 原版写的有问题
    std::vector<double> dists ;
    double fx,fy;
    fx = robot_state[0] + L *cos(robot_state[2]);
    fy = robot_state[1] + L *sin(robot_state[2]);
    for(auto xy : refer_path)
    {

        double distance = sqrt( pow(fx- xy[0], 2 ) + pow(fy - xy[1], 2)      );
        dists.push_back(distance);
    }
    double min_ind = min_element(dists.begin(), dists.end()) - dists.begin();
    return min_ind;
}

double Stanley::normalizeAngle(double angle)
{
    /*
    角度正则化
    */
    while(angle >Pi)
    {
        angle-=2*Pi;

    }

    while(angle< -Pi)
    {
        angle+=2*Pi;
    }
    return angle ;
}


std::vector<double> Stanley::stanelyControl(std::vector<double>robot_state, std::vector<std::vector<double>> refer_path)
{
    double current_index = this->calTargetIndex(robot_state,refer_path);
    std::vector<double> current_ref_point;
    if (current_index >= refer_path.size())
    {
        current_index-=1;
        current_ref_point = refer_path[refer_path.size() - 1 ];

    }
    else
    {
        current_ref_point = refer_path[current_index];
    }
    //横向误差
    double e_y,e_y1;
    //道路的航向角 切线与x轴的夹角
    double psi_t = current_ref_point[2];
    double  L=2;//车身的长度 要做修改 原版写的有问题
    double fx,fy;
    fx = robot_state[0] + L *cos(robot_state[2]);
    fy = robot_state[1] + L *sin(robot_state[2]);


    double delta_ey = (fx -current_ref_point[0]) * cos(robot_state[2]-Pi/2) + ( fy - current_ref_point[1])  * sin(robot_state[2]-Pi/2);
    
    //公式是fx fy 是目标点-车辆质心点 指向目标点， 我们是希望向 目标点走 之后 我们这个的fx和fy是 质心-目标 所以每个都要 有个-1   我们的fx是 车辆质心点 - 轨迹的参考点   之后 向量旋转90度
    //frenet坐标系下，以前轮中心为 为原点构建出一个坐标系，横向误差是多大
    // delta_ey1 这个就是直接按照选择角度 得到的 旋转90从cos 变为sin  之后海斯负的  这个是看30度 之后+90度后结果
    double delta_ey1 = -1 * (fx -current_ref_point[0]) *  -1 * sin(robot_state[2]) + -1 *( fy - current_ref_point[1])  * cos(robot_state[2]);
    // 这个是逆时针走90度 套用 -1* dx*sin(theta) + dy * cos(theta ) 这个方法计算
    // 单位法向量 是 cos(theta), sin(theta) 直接旋转90度 套用上面的公式， 之后 相对距离是
    double delta_ey2 = (fx -current_ref_point[0]) *-1* cos(robot_state[2]+Pi/2) + -1 *( fy - current_ref_point[1])  * sin(robot_state[2]+Pi/2);
    
    bool f1;
    f1 = delta_ey ==delta_ey1;
    double mi= delta_ey-delta_ey1;
    // std::cout << delta_ey<<  "   delta_ey  "  <<delta_ey1<<" delta_ey2 "<< delta_ey2<<std::endl;

    //右侧为正 反之为负
    // 计算横向误差e_y
    // 参考自https://blog.csdn.net/renyushuai900/article/details/98460758
    int target,target1,target2,target3;
    if((robot_state[0]-current_ref_point[0])*psi_t-(robot_state[1]-current_ref_point[1])>0){
    //if((robot_state[1]-current_ref_point[1])*cos(psi_t)-(robot_state[0]-current_ref_point[0])*sin(psi_t)<=0){
        e_y = sqrt(pow(current_ref_point[0]-robot_state[0],2)+pow(current_ref_point[1]-robot_state[1],2));
        target = 1;
    }else{
        e_y = -sqrt(pow(current_ref_point[0]-robot_state[0],2)+pow(current_ref_point[1]-robot_state[1],2));
        target = -1;
    }
    if(fx * cos(current_ref_point[2] ) - fy * sin(current_ref_point[2]))
    {
        e_y1 = sqrt(pow(current_ref_point[0]-robot_state[0],2)+pow(current_ref_point[1]-robot_state[1],2));
    }
    else{
        e_y1 = -sqrt(pow(current_ref_point[0]-robot_state[0],2)+pow(current_ref_point[1]-robot_state[1],2));
    }
    std::cout << delta_ey<<  "   delta_ey1:  "  <<delta_ey1<<" delta_ey: "<< delta_ey2<<" e_y1 "<<e_y1<<std::endl;

    //# 通过公式(5)计算转角,符号保持一致
    double psi = robot_state[2];
    double v = robot_state[3];
    
    double theta_e = psi_t - psi;
    //delta_ey 作为横向误差效果最好i
    double delta_e = atan2(k* delta_ey1,v);
    double delta = this->normalizeAngle(delta_e+theta_e);
    return {delta,current_index};

}






