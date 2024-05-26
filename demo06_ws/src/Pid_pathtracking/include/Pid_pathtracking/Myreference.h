#ifndef MY_REFERENCE_PATH
#define MY_REFERENCE_PATH



#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
//声明一个返回 双层嵌套的vector的数据 vector<vector<double>>  第一层vector 每个元素是 vector  这个vector 每个是double类型和苏剧
//包含数据的 x,y,psi 航向角
vector<vector<double> > my_reference_vector();

struct reference_struct
{
    vector<vector<double> > path;
    vector<double> path_x;
    vector<double> path_y;
};


reference_struct generate_path();

struct ref22
{
    int x;
};

#endif