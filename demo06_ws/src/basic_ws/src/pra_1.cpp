#include"ros/ros.h"

#include <eigen3/Eigen/Dense>

void base1()
{
    Eigen::Matrix<double, 3, 3> A;               // Fixed rows and cols. Same as Matrix3d.
    Eigen::Matrix<double, 3, Eigen::Dynamic> B;         // Fixed rows, dynamic cols.
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> C;   // Full dynamic. Same as MatrixXd.
    Eigen::Matrix<double, 3, 3, Eigen::RowMajor> E;     // Row major; default is column-major.
    Eigen::Matrix3f P, Q, R;                     // 3x3 float matrix.
    Eigen::Vector3f x, y, z;                     // 3x1 float matrix.
    Eigen::RowVector3f a, b, c;                  // 1x3 float matrix.
    Eigen::VectorXd v;                           // Dynamic column vector of doubles
    A<<1,2,3,4,5,6,7,8,9;
    std::cout<<A<<std::endl;
    // Eigen          // Matlab           // comments
    // length(x)        // vector size
    std::cout<< A.size() <<std::endl;
    std::cout<< A.rows() <<std::endl;         
    // size(C,1)        // number of rows
    //C.cols()    ;      // size(C,2)        // number of columns
    std::cout<< A.cols() <<std::endl;      
    //x(0)       ;       // x(i+1)           // Matlab is 1-based
    std::cout<< A(0) <<std::endl;      

    //C(1,1)      ;      // C(i+1,j+1)       //
    std::cout<< A(1,2) <<std::endl;     
}

int main(int argc,char* argv[])
{

    base1();

    return 0;
}