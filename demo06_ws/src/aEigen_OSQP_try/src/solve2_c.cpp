#include <iostream>
#include <eigen3/Eigen/Dense>
 
//using Eigen::MatrixXd;

 

#include <iostream>
// osqp-eigen
#include <OsqpEigen/OsqpEigen.h>


 
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;
 
using namespace std;
Eigen::SparseMatrix<double> hessian;
Eigen::VectorXd gradient;
Eigen::SparseMatrix<double> linearMatrix;
Eigen::VectorXd lowerBound;
Eigen::VectorXd upperBound;

//传入的对象是 OsqpEigen的 求解器的实参对象  
int initMat(OsqpEigen::Solver& solver)
{
    //我们是3个变量
    //4个约束
    unsigned int numOfVar = 3;
    unsigned int numOfCons = 4;
    solver.data()->setNumberOfVariables(numOfVar);
    solver.data()->setNumberOfConstraints(numOfCons);
 
    //初始化我们的海森矩阵 系数  乘以便利
    hessian.resize(numOfVar, numOfVar);
    //这个是海森矩阵 右侧的结果
    gradient.resize(numOfVar);
    // 我们的约束矩阵 是 几个，行是约束的数量 右侧是说明我们的便利数， 构建矩阵
    linearMatrix.resize(numOfCons, numOfVar);
    //上下限
    lowerBound.resize(numOfCons);
    upperBound.resize(numOfCons);
 
 
    hessian.insert(0, 0) = 1;
    hessian.insert(0, 1) = -1;
    hessian.insert(0, 2) = 1;
    hessian.insert(1, 0) = -1;
    hessian.insert(1, 1) = 2;
    hessian.insert(1, 2) = -2;
    hessian.insert(2, 0) = 1;
    hessian.insert(2, 1) = -2;
    hessian.insert(2, 2) = 4;
    //cout << "hessian" << hessian << endl;

    //海森矩阵的两种实现方式，矩阵导入的两种方法

    /* hessian << 1, -1, 1,
              -1, 2, -2,
               1, -2, 4;*/
    //这个是常数项 求导数中的常数项
    gradient << 2, -3, 1;
    
    linearMatrix.insert(0, 0) = 1;
    linearMatrix.insert(1, 1) = 1;
    linearMatrix.insert(2, 2) = 1;
    linearMatrix.insert(3, 0) = 1;
    linearMatrix.insert(3, 1) = 1;
    linearMatrix.insert(3, 2) = 1;
    /*linearMatrix << 1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
                    1, 1, 1;*/
 
    lowerBound << 0, 0, 0, 0.5;
    upperBound << 1, 1, 1, 0.5;
    //这是校验的作用 还没有弄懂
    if (!solver.data()->setHessianMatrix(hessian)) return false;
    if (!solver.data()->setGradient(gradient)) return false;
    if (!solver.data()->setLinearConstraintsMatrix(linearMatrix)) return false;
    if (!solver.data()->setLowerBound(lowerBound)) return false;
    if (!solver.data()->setUpperBound(upperBound)) return false;
 
    return true;
}
 
int main() {
    OsqpEigen::Solver solver;
 
    // set the solver
    solver.settings()->setWarmStart(true);
 
    // instantiate the solver
    if (initMat(solver)) {
        if (!solver.initSolver()) return 1;
    }
    else {
        cout << "initilize QP solver failed" << endl;
        return 1;
    }
 
    // solve
    solver.solve();
 
    Eigen::VectorXd QPSolution;
    QPSolution = solver.getSolution();
    
    cout << "x1 = " << QPSolution[0] << endl
        << "x2 = " << QPSolution[1] << endl
        << "x3 = " << QPSolution[2] << endl;
}
