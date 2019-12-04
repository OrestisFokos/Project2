#ifndef FILE_H
#define FILE_H
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <tuple>


typedef double new_type;

using point = std::vector<new_type>;
using curve    = std::vector <point>;
using vec_curve = std::vector<curve>;

using namespace std;






typedef struct InputPoints{
  vector <string> ids;
  vector < vector <new_type> > dimensions;
}InputPoints;

//kathe curve einai vector apo tuples me x,y diastaseis k exei k ena curve id
typedef struct InputCurves{
  vector <string> ids;
  vec_curve dimensions;
}InputCurves;

/* oi 2 autes domes ws centroid exoun ena stoixeio kai oxi pointer se stoixeio
epeidh uparxei periptwsh to centroid na min einai uparkto stoixeio */
typedef struct PointCluster{
  point  centroid;
  vector <point *> objects;
}PointCluster;

typedef struct CurveCluster{
  curve centroid;
  vector <curve *> objects;
}CurveCluster;



typedef double new_type;

InputPoints * read_input_points(string filename);

InputCurves* read_input_curves (string filename);

vector<double>  spl(string str);



#endif //FILE_H
