#include <iostream>
#include <fstream>
#include "point.h"

using namespace std;
 Points::Points(int n_points, int n_g){
	npoints = n_points;
	vector <Point> P;
	ng = n_g;
}

Point::Point(int ndimensions,int ng){
	ndimensions = ndimensions;
	ng = ng;
	//G[]  ...       diavasma arxeiou gia na thesw times sta g
}


/*
void Point::display() {
    for (auto it = dimensions.begin(); it != dimensions.end(); ++it) {
        cout << *it << " ";
    }
}
*/

/*
vector<int> Point::getPoint() {
     return dimensions;
 }
*/

void Point::set_point_id(const char * id){
	point_id = string(id);//nomizw den xreiazetai na to kanw memcpy?
}

string Point::get_point_id(){
	return point_id;
}

void Point::set_g_values(vector <int> g_values){
    G = g_values;
}

vector <int> Point::get_g_values(){
  return G;
}
/*
void Point::set_distances(vector<double>dist){
	distances = dist;
}

vector<double> Point::get_distances(){
	return distances;
} */
