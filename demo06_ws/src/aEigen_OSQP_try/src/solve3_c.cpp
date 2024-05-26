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
 
/*

read this 文章就好了


https://yunchengjiang.blog.csdn.net/article/details/115122792?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-115122792-blog-126568314.235%5Ev43%5Epc_blog_bottom_relevance_base2&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-1
15122792-blog-126568314.235%5Ev43%5Epc_blog_bottom_relevance_base2&utm_relevant_index=1




*/

int initMat(OsqpEigen::Solver& solver)
{
    // 我们构建的线性2次规划函数  我们是两个变量 3个约束 
    
    int NumberOfVariables = 2;   
    int NumberOfConstraints = 3; 
    solver.data()->setNumberOfVariables(NumberOfVariables);     //设置A矩阵的列数，即n
    solver.data()->setNumberOfConstraints(NumberOfConstraints); //设置A矩阵的行数，即m
    //初始化矩阵 副值
    hessian.resize(2, 2);
    hessian.insert(0, 0) = 1;
    hessian.insert(1, 0) = -1;
    hessian.insert(0, 1) = -1;
    hessian.insert(1, 1) = 2;
    std::cout << "hessian:" << std::endl
                << hessian << std::endl;
    //海森矩阵的常数项 
    gradient.resize(2);
    gradient << -2, -6;

    std::cout << "gradient:" << std::endl
                << gradient << std::endl;
    //设定约束 每个变量前的系数
    linearMatrix.resize(3, 2);
    linearMatrix.insert(0, 0) = 1;
    linearMatrix.insert(0, 1) = 1;
    linearMatrix.insert(1, 0) = -1;
    linearMatrix.insert(1, 1) = 2;
    linearMatrix.insert(2, 0) = 2;
    linearMatrix.insert(2, 1) = 1;
    std::cout << "linearMatrix:" << std::endl
                << linearMatrix << std::endl;
    // 约束对应的结果 小于等于3 那就是上界是3 下界负无穷
    lowerBound.resize(3);
    lowerBound << -OsqpEigen::INFTY, -OsqpEigen::INFTY, -OsqpEigen::INFTY;
    std::cout << "lowerBound:" << std::endl
                << lowerBound << std::endl;

    upperBound.resize(3);
    upperBound << 2, 2, 3;
    std::cout << "upperBound:" << std::endl
                << upperBound << std::endl;
    // 出现等号约束，上下限约束成一个值
    // 每个变量的取值范围，可以变换成 不等于约束 x1 [-2, 3] 那就 这行的系数是1，0  
    // 上界3 下界设置成2
    

    if (!solver.data()->setHessianMatrix(hessian))
        return 1; //设置P矩阵
    if (!solver.data()->setGradient(gradient))
        return 1; //设置q or f矩阵。当没有时设置为全0向量
    if (!solver.data()->setLinearConstraintsMatrix(linearMatrix))
        return 1; //设置线性约束的A矩阵
    if (!solver.data()->setLowerBound(lowerBound))
        return 1; //设置下边界
    if (!solver.data()->setUpperBound(upperBound))
        return 1; //设置上边界

    // instantiate the solver
    if (!solver.initSolver())
        return 1;

    Eigen::VectorXd QPSolution;

    // solve the QP problem
    if (!solver.solve())
        return 1;

    // get the controller input
    clock_t time_start = clock();
    clock_t time_end = clock();
    time_start = clock();
    QPSolution = solver.getSolution();
    time_end = clock();
    std::cout << "time use:" << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms" << std::endl;

    std::cout << "QPSolution:" << std::endl
                << QPSolution << std::endl;

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
        << "x2 = " << QPSolution[1] << endl;
        //<< "x3 = " << QPSolution[2] << endl;
}
