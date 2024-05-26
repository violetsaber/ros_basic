#include"Pid_pathtracking/Myreference.h"



vector<vector<double>> my_reference_vector()
{
    /*
    在定义的时候 vector必须包含 给定一个长度  初始化
    未初始化的 refer_path：在函数 my_reference_vector 中，refer_path 被声明为一个二维 vector，但在使用之前没有进行初始化。
    在C++中， 如果一个 vector 没有被初始化，尝试通过索引访问它的元素将导致未定义行为。
    */
    int num=10;
    vector<vector<double> > refer_path;
    vector<double> refer_x(num),refer_y(num);
    refer_path.resize(num,vector<double>(2));
    for(int i=0;i<num;i++)
    {
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
//        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    }
    return refer_path;

}

reference_struct generate_path()
{   
    int num=10;
    vector<vector<double> > refer_path;
    vector<double> refer_x(num),refer_y(num);
    refer_path.resize(num,vector<double>(2));
    for(int i=0;i<num;i++)
    {
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
//        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    }
    reference_struct rf1;
    rf1.path_x = refer_x;
    rf1.path_y = refer_y;
    rf1.path = refer_path;
    return rf1;
}
ref22 gp()
{
    ref22 ref1;
    ref1.x=1;
    return ref1;
}
