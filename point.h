#ifndef POINT_H
#define POINT_H

#include <vector>
#include "file.h"

using namespace std;

class Point
{
	vector<int> dimensions;
	vector<int> G;
public:


//	logika den tha kratame vectors !  vector<int> dimensions;


	string point_id;
	Point(int D,int ng,vector<int> p2); //constructor
//	vector <double> distances;	//den tha ta krataw, tha krataw apla to nn distance (meta out kan auto)
	double avg_nn_distance;
	Point(int D,int ng); //constructor
	void set_point_id(const char *id);
	string get_point_id();
	void set_g_values(vector <int>g_values);
	vector<int> get_g_values();
	void display();
	vector<int> getPoint();

	/* void set_distances(vector<double>distances);
	vector<double> get_distances(); */
};

class Points
{

public:
	int ndimensions;
	int npoints;
	int ng;	//arithmos apo g?
	vector <Point> P;	//diavasma apo arxeio gia tis times tous
	Points(int n_points, int ng); //constructor
};

#endif //POINT_H
