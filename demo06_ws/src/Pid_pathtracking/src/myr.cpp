
#include"ros/ros.h"
#include<cmath>
#include <algorithm>

#include"Pid_pathtracking/Myreference.h"
#include<vector>
#include"matplotlibcpp.h"
namespace plt = matplotlibcpp;

vector<int> createVector() {
    vector<int> myVector = {1, 2, 3, 4, 5};
    return myVector;
}
vector<vector<double>> my_reference_vector1()
{
    vector<vector<double> > refer_path;
    refer_path.resize(5, vector<double>(2));
    vector<double> refer_x,refer_y;
    for(int i=0;i<5;i++)
    {
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    }
    return refer_path;

}

void f1()
{
    vector<int> a=createVector();
    for(auto x:a)
    {
        cout<<x<<endl;
    }
}


void f2()
{
    vector<vector<double>> a=my_reference_vector1();
    for(auto x:a)
    {
        for (auto y:x)
        {
            cout<< y <<endl;
        }
    }
}
void f3()
{
    reference_struct a=generate_path();
    for(auto x:a.path)
    {
        for (auto y:x)
        {
            cout<< y <<endl;
        }
    }
}
void f4()
{
    vector<vector<double>> a=my_reference_vector();
    for(auto x:a)
    {
        for (auto y:x)
        {
            cout<< y <<endl;
        }
    }
}
int main(int argc,char* argv[])
{

    
    vector<vector<double>>refer_path(1000,vector<double>(2));
    vector<double>refer_x,refer_y; //保存参考数据用于画图
    reference_struct  rs ;
    rs.path=refer_path; 
    //vector<vector<double>>  rf2 = my_reference_vector();
    cout<<"f1"<<endl;
    f1();
    cout<<"f2"<<endl;
    f2();
    cout<<"***********f3**************"<<endl;
    f3();
    cout<<"***********f4**************"<<endl;
    f4();
  
    //cout<<rs.path<<endl;
    // 生成参考轨迹
    /* for(int i=0;i<1000;i++){
        refer_path[i][0]=0.1*i;
        refer_path[i][1]=2*sin(refer_path[i][0]/3.0);
        refer_x.push_back(refer_path[i][0]);
        refer_y.push_back(refer_path[i][1]);
//        cout<<refer_path[i][0]<<" ,"<<refer_path[i][1]<<endl;
    } */
    
    /* plt::clf();
    plt::plot(refer_x,refer_y,"b--");

    plt::grid(true);
    plt::ylim(-2.5,2.5);
    //plt::pause(0.01);
    //plt::save(filename);
    plt::show(); */
    /* for (auto x1 : refer_x)
    {
        cout<<x1<<endl;
    } */
    return 0;
}