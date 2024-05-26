#include"rear_wheel_feedback/rear_my_reference.h"


/**
 * 构造函数，求解出参考轨迹点上的曲率等信息
 */

MyReferencePath::MyReferencePath() 
{
    //轨迹要给出一个长度 这样在返回轨迹的时候 就不会有问题
    refer_path = vector<vector<double>>(1000, vector<double>(4));
    // 生成参考轨迹
    //生成x和y
    for (int i = 0; i < 1000; i++) {
        refer_path[i][0] = 0.1 * i;
        refer_path[i][1] = 2 * sin(refer_path[i][0] / 3.0) + 2.5 * cos(refer_path[i][0] / 2.0);

        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
    }
    double dx,dy,ddx,ddy;
    for(int i=0;i<refer_path.size();i++){
        if (i==0){
            // 
             dx = refer_path[i+1][0] - refer_path[i][0];
             dy = refer_path[i+1][1] - refer_path[i][1];
             ddx = refer_path[2][0] + refer_path[0][0] - 2*refer_path[1][0];
             ddy = refer_path[2][1] + refer_path[0][1] - 2*refer_path[1][1];
        }else if(i==refer_path.size()-1){
             dx = refer_path[i][0] - refer_path[i-1][0];
             dy = refer_path[i][1] - refer_path[i-1][1];
             ddx = refer_path[i][0] + refer_path[i-2][0] - 2*refer_path[i-1][0];
             ddy = refer_path[i][1] + refer_path[i-2][1] - 2*refer_path[i-1][1];
        }else{
             dx = refer_path[i+1][0] - refer_path[i][0];
             dy = refer_path[i+1][1] - refer_path[i][1];
             ddx = refer_path[i+1][0] + refer_path[i-1][0] - 2*refer_path[i][0];
             ddy = refer_path[i+1][1] + refer_path[i-1][1] - 2*refer_path[i][1];
        }
        refer_path[i][2] = atan2(dy,dx);//yaw
        //计算曲率:设曲线r(t) =(x(t),y(t)),则曲率k=(x'y" - x"y')/((x')^2 + (y')^2)^(3/2).
        //参考：https://blog.csdn.net/weixin_46627433/article/details/123403726
        refer_path[i][3]= (ddy * dx - ddx * dy) / pow((dx * dx + dy * dy), 3 / 2) ;// 曲率k计算
    }
}
/**
 * 角度归一化
 * @param angle
 * @return
 */
double MyReferencePath::normalizeAngle(double angle) 
{
    while(angle>PI){
        angle-=2.0*PI;
    }
    while(angle<-PI){
        angle+=2.0*PI;
    }
    return angle;
}

vector<double> MyReferencePath::calcTrackError(vector<double> robot_state)
{

    double x = robot_state[0] , y = robot_state[1] ; 
    vector<double> d_x(this->refer_path.size()),d_y(this->refer_path.size()), d(this->refer_path.size());
    for(int i=0;i<this->refer_path.size();i++)
    {
        d_x[i] = this->refer_path[i][0] - x;
        d_y[i] = this->refer_path[i][1] - y;
        d[i] = sqrt(d_x[i] * d_x[i] + d_y[i] * d_y[i]);


    }
    double min_index = min_element(d.begin() , d.end()) - d.begin();
    double yaw = refer_path[min_index][2];//轨迹上的航向角
    double k = refer_path[min_index][3];//曲线的斜率 这个frenet的切线斜率
    double error = d[min_index];//误差
    //判断公司sin(yaw- refer[min_index][2])
    double angle = normalizeAngle(yaw- atan2(d_y[min_index],d_x[min_index]));
    double fx = d_x[min_index],fy = d_y[min_index];
    int flag1,flag2,flag3;
    double n1,n2,n3;

    //这个是计算的方法 得到1和-1 计算结果
    /* n1= sin(angle)*sin(refer_path[min_index][2] )   -  cos(angle)*cos(refer_path[min_index][2]) ; */
    n1= sin(angle)*sin( yaw )   -  cos(angle)*cos( yaw ) ;
    if ( n1>0
        //sin(angle)*sin(refer_path[min_index][2] )   -  cos(angle)*cos(refer_path[min_index][2])  >0 
        )
    {
        flag1 =1;
    }
    else
    {
        flag1=-1;
    }

    // 基于据sign函数 计算n2 判断方向的正负
    n2 =-1*fy * cos(refer_path[min_index][2]) - -1*fx*sin(refer_path[min_index][2]);
    if ((  -1*fy * cos(normalizeAngle(refer_path[min_index][2]) )- (-1)* sin(normalizeAngle(refer_path[min_index][2]) *fx )    )>0)
    {
        flag2=1;
    }
    else
    {

        flag2 =-1;
    }


    if(angle<0)
    {
        error*=-1;
        flag3 = -1;
    }
    else
    {
        flag3 = 1;
    }
    cout<<"flag1: " <<flag1<<"flag2: " <<flag2<<"flag3 "<<flag3<<endl;
    cout<<"n1: " <<n1<<"n2: " <<n2<<"n3 "<<angle<< "error " <<error <<endl;
    return {error,k,yaw,min_index};

}

/**
 * 计算参考轨迹点，统一化变量数组，只针对MPC优化使用
 * @param robot_state 车辆的状态(x,y,yaw,v)
 * @param param 超參數
 * @param dl Defaults to 1.0.
 * @return {xref, dref, ind}结构体
 */
refTraj MyReferencePath::calc_ref_trajectory(vector<double> robot_state,parameters param, double dl) {
    vector<double>track_error = calcTrackError(robot_state);//e,k,ref_yaw,ind
    double e = track_error[0],k=track_error[1],ref_yaw=track_error[2],ind = track_error[3];
    refTraj ref_traj;
    ref_traj.xref=MatrixXd (param.NX,param.T+1);
    ref_traj.dref = MatrixXd (param.NU,param.T);
    int ncourse = refer_path.size();
    ref_traj.xref(0,0)=refer_path[ind][0];
    ref_traj.xref(1,0)=refer_path[ind][1];
    ref_traj.xref(2,0)=refer_path[ind][2];
    //参考控制量[v,delta]
    double ref_delta = atan2(param.L*k,1);
    for(int i=0;i<param.T;i++){
        ref_traj.dref(0,i)=robot_state[3];
        ref_traj.dref(1,i)=ref_delta;
    }

    double travel = 0.0;

    for(int i=0;i<param.T+1;i++){
        travel+=abs(robot_state[3])*param.dt;

        double dind = (int)round(travel/dl);

        if(ind+dind<ncourse){
            ref_traj.xref(0,i)=refer_path[ind+dind][0];
            ref_traj.xref(1,i)=refer_path[ind+dind][1];
            ref_traj.xref(2,i)=refer_path[ind+dind][2];
        }else{
            ref_traj.xref(0,i)=refer_path[ncourse-1][0];
            ref_traj.xref(1,i)=refer_path[ncourse-1][1];
            ref_traj.xref(2,i)=refer_path[ncourse-1][2];
        }
    }
    return ref_traj;

}

