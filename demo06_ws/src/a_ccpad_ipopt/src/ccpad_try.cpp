#include <iostream>
#include <cppad/ipopt/solve.hpp>

using namespace std;

namespace {
using CppAD::AD;
class FG_eval {
public:
    typedef CPPAD_TESTVECTOR(AD<double>) ADvector;
    void operator()(ADvector& fg, const ADvector& x)
    {
        assert(fg.size() == 3);
        assert(x.size() == 4);
        // variables
        AD<double> x1 = x[0];
        AD<double> x2 = x[1];
        AD<double> x3 = x[2];
        AD<double> x4 = x[3];
        // f(x) objective function
        fg[0] = x1 * x4 * (x1 + x2 + x3) + x3;
        // constraints
        fg[1] = x1 * x2 * x3 * x4;
        fg[2] = x1 * x1 + x2 * x2 + x3 * x3 + x4 * x4;
        return;
    }

};

}

bool get_started(void)
{
    bool ok = true;
    size_t i;
    typedef CPPAD_TESTVECTOR(double) Dvector;

    size_t nx = 4; // number of varibles
    size_t ng = 2; // number of constraints
    Dvector x0(nx); // initial condition of varibles
    x0[0] = 1.0;
    x0[1] = 5.0;
    x0[2] = 5.0;
    x0[3] = 1.0;

    // lower and upper bounds for varibles
    Dvector xl(nx), xu(nx);
    for(i = 0; i < nx; i++)
    {
        xl[i] = 1.0;
        xu[i] = 5.0;
    }
    Dvector gl(ng), gu(ng);
    gl[0] = 25.0;    gu[0] = 1.0e19;
    gl[1] = 40.0;    gu[1] = 40.0;
    // object that computes objective and constraints
    FG_eval fg_eval;

    // options
    string options;
    // turn off any printing
    options += "Integer print_level  0\n";
    options += "String sb            yes\n";
    // maximum iterations
    options += "Integer max_iter     10\n";
    //approximate accuracy in first order necessary conditions;
    // see Mathematical Programming, Volume 106, Number 1,
    // Pages 25-57, Equation (6)
    options += "Numeric tol          1e-6\n";
    //derivative tesing
    options += "String derivative_test   second-order\n";
    // maximum amount of random pertubation; e.g.,
    // when evaluation finite diff
    options += "Numeric point_perturbation_radius   0.\n";
    /*
    
    这些代码行是设置IPOPT求解器的选项字符串。以下是各个选项的解释：

    "Integer print_level 0\n"：将输出级别设置为0，意味着在运行过程中不会显示任何详细信息或进度。如果你希望看到求解过程中的信息，可以将print_level值设为一个大于0的数字。

    "String sb yes\n"：这个选项可能是指求解后的解决方案（Solution Breakdown）是否应该被打印。"yes" 表示开启此功能，但请注意，这并非IPOPT的标准选项，可能是用户自定义或者特定环境下的设置。

    "Integer max_iter 10\n"：设置了最大迭代次数为10次。这意味着如果优化算法在达到10次迭代之前没有收敛，它将停止并返回当前结果。

    "Numeric tol 1e-6\n"：设置了一个相对精度为1e-6的第一阶必要条件。这是算法在满足此精度时认为已经找到近似最优解的一个标准。

    "String derivative_test second-order\n"：指定了导数测试类型为二阶，意味着IPOPT会检查模型的二阶导数（Hessian矩阵）以验证其连续性。这对于确保问题的稳定性和优化算法的性能很有用。

    "Numeric point_perturbation_radius 0.\n"：设置了用于有限差分法估计导数时的最大随机扰动幅度。值为0表示禁用或使用极小的扰动，这可能会影响计算效率和准确性。

    这些选项可以通过调整来控制IPOPT的行为，适应不同的优化问题需求。记得在调用求解器前更新options字符串。

    
    */

    CppAD::ipopt::solve_result<Dvector> solution; // solution
    CppAD::ipopt::solve<Dvector, FG_eval>(options, x0, xl, xu, gl, gu, fg_eval, solution); // solve the problem

    cout<<"solution: "<<solution.x<<endl;

    //
    //check some of the solution values
    //
    ok &= solution.status == CppAD::ipopt::solve_result<Dvector>::success;
    //
    double check_x[]  = {1.000000, 4.743000, 3.82115, 1.379408};
    double check_zl[] = {1.087871, 0.,       0.,       0.      };
    double check_zu[] = {0.,       0.,       0.,       0.      };
    double rel_tol    = 1e-6; // relative tolerance
    double abs_tol    = 1e-6; // absolute tolerance
    for(i = 0; i < nx; i++)
    {
        ok &= CppAD::NearEqual(
                    check_x[i], solution.x[i], rel_tol, abs_tol);
        ok &= CppAD::NearEqual(
                    check_zl[i], solution.zl[i], rel_tol, abs_tol);
        ok &= CppAD::NearEqual(
                    check_zu[i], solution.zu[i], rel_tol, abs_tol);
    }

    return ok;
}

int main()
{
    cout << "CppAD : Hello World Demo!" << endl;
    get_started();
    return 0;
}
