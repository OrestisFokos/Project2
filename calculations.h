#ifndef LSH_CALCULATIONS_H
#define LSH_CALCULATIONS_H
#include <vector>
#include <string>
#include "file.h"

using namespace std;


vector<new_type> a_calculation(vector<new_type> p,vector<double> r);  //project x to a in d-dimensional grid shifted by s,cell size w
long long h_calculation(vector<new_type> a);
//vector<double> f_calculation();
vector<double> randomVector(); //uniformly distributed vector in [0,w),w>>r

double randomNumber(double x,double y); // uniform distribution
double distance(vector<new_type>, vector<new_type>, string distance_type);
double min_C(vector<vector<new_type>> p, vector<vector<new_type>> q, int x, int y); // dynamic

long long modularSum(int a,int b);//if needed,prob not
long long modularPow(int m,int d, int M);

long long h_calculation(vector<new_type> a);
long long h2_calculation(vector<new_type> a);//if needed,probably not

int g_concat(vector<new_type> p, vector<double> *s); //revaluate g for query
int binarytoDec(int *arrbin);
int decToBinaryConcat(vector<new_type> h_f);


#endif //LSH_CALCULATIONS_H