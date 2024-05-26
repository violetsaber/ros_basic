#include"lqr_control/lqr_c.h"


LQRContronl::LQRContronl(int n):N(n)
{
    //初始化函数
}


/**
 * 解代数里卡提方程
 * @param A 状态矩阵A
 * @param B 状态矩阵B
 * @param Q Q为半正定的状态加权矩阵, 通常取为对角阵；Q矩阵元素变大意味着希望跟踪偏差能够快速趋近于零；
 * @param R R为正定的控制加权矩阵，R矩阵元素变大意味着希望控制输入能够尽可能小。
 * @return
 */
MatrixXd LQRContronl::calRicatti(MatrixXd A, MatrixXd B, MatrixXd Q , MatrixXd R)
{
    /* MatrixXd P = Q;
    MatrixXd P_;
    for ( int i =0 ; i<this->N ; i++ )
    {

        
        //求解Riccati方程  左侧是Pn-1  右侧的P是Pn 是上一个时刻的结果
        //P_ = Q+A.transpose()*P*A-A.transpose()*P*B*(R+B.transpose()*P*B).inverse()*B.transpose()*P*A;           
        MatrixXd P_ =  Q + A.transpose() *  P * A  - A.transpose() * P * B * ( R + B.transpose() * P * B ).inverse() * B.transpose() * P * A;
        if((P_-P).maxCoeff()<EPS&&(P-P_).maxCoeff()<EPS)
        {
            break;
        }
        P = P_;
    }
    return P_; */
    MatrixXd Qf= Q;
    MatrixXd P = Qf;
    MatrixXd P_;
    for(int i=0;i<N;i++){
        P_ = Q+A.transpose()*P*A-A.transpose()*P*B*(R+B.transpose()*P*B).inverse()*B.transpose()*P*A;
        //小于预设精度时返回
        if((P_-P).maxCoeff()<EPS&&(P-P_).maxCoeff()<EPS)break;
        //if((P_-P).cwiseAbs().maxCoeff()<EPS)break;

        P = P_;

    }
    return P_;
}


/*

double LQRControl::lqrControl(vector<double> robot_state, vector<vector<double>> refer_path, double s0, MatrixXd A, MatrixXd B,
                       MatrixXd Q, MatrixXd R) {
    MatrixXd X(3,1);
    X<<robot_state[0]-refer_path[s0][0],robot_state[1]-refer_path[s0][1],robot_state[2]-refer_path[s0][2];
    MatrixXd P = calRicatti(A,B,Q,R);
    MatrixXd K = -(R+B.transpose()*P*B).inverse()*B.transpose()*P*A;
    MatrixXd u = K*X; //[v-ref_v,delta-ref_delta]

    return u(1,0);
*/

double LQRContronl::lqrControl(vector<double> robot_state, vector<vector<double>> refer_path, double s0, MatrixXd A, MatrixXd B,
        MatrixXd Q, MatrixXd R)
{
        MatrixXd X(3,1);
        // 控制的 是车辆的质心位置和 参考点的 误差量
        X<<robot_state[0]-refer_path[s0][0],robot_state[1]-refer_path[s0][1],robot_state[2]-refer_path[s0][2];
        MatrixXd P = this->calRicatti(A,B,Q,R);
        MatrixXd K = -(R + B.transpose() * P * B ).inverse() * B.transpose() * P * A ;
        //u = -kx  上面的K 是已经有负号了
        MatrixXd u = K * X ;//[v-ref_v,delta-ref_delta]  eigen的索引方法() 小括号 才可以两个参数  [] 只能是一个参赛 
        //cout<<u.rows() << "   "<< u.cols() << endl;


        return u(1,0);
}
MatrixXd LQRContronl::lqrControl1(vector<double> robot_state, vector<vector<double>> refer_path, double s0, MatrixXd A, MatrixXd B,
        MatrixXd Q, MatrixXd R)
{
        MatrixXd X(3,1);
        // 控制的 是车辆的质心位置和 参考点的 误差量
        X<<robot_state[0]-refer_path[s0][0],robot_state[1]-refer_path[s0][1],robot_state[2]-refer_path[s0][2];
        MatrixXd P = this->calRicatti(A,B,Q,R);
        MatrixXd K = -(R + B.transpose() * P * B ).inverse() * B.transpose() * P * A ;
        //u = -kx  上面的K 是已经有负号了
        MatrixXd u = K * X ;//[v-ref_v,delta-ref_delta]  eigen的索引方法() 小括号 才可以两个参数  [] 只能是一个参赛 
        cout<<u.rows() << "   "<< u.cols() << endl;

        cout<<u<<endl;
        return u;
}