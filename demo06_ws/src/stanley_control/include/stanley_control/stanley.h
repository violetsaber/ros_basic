#ifndef STANLEY_QIDAI
#define STANLEY_QIDAI 

#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>
// using namespace std;
#define Pi 3.1415926
class Stanley
{
/*

private:
    double k;
public:
    Stanley(double k);
    double calTargetIndex(vector<double>robot_state, vector<vector<double>>refer_path);
    double normalizeAngle(double angle);
    vector<double> stanleyControl( vector<double>robot_state, vector<vector<double>>refer_path);
    };

*/
private:
    double k;
public:
    Stanley(double k);
    double calTargetIndex(std::vector<double> robot_state, std::vector<std::vector<double>> refer_path);
    double normalizeAngle(double angle);
    std::vector<double> stanelyControl(std::vector<double>robot_state,std::vector<std::vector<double>> refer_path);

};

#endif