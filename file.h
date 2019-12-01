#ifndef FILE_H
#define FILE_H
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <tuple>

using point = std::vector<double>;
using curve    = std::vector <point>;
using vec_curve = std::vector<curve>;

using namespace std;

typedef double new_type;




typedef struct InputPoints{
  vector <string> ids;
  vector < vector <new_type> > dimensions;
}InputPoints;

//kathe curve einai vector apo tuples me x,y diastaseis k exei k ena curve id
typedef struct InputCurves{
  vector <string> ids;
  vector < vector <tuple <new_type,new_type> > > dimensions;
}InputCurves;

typedef double new_type;

InputPoints * read_input_points(string filename);

InputCurves * read_input_curves(string filename);
vec_curve read_input_curves2 (string filename);

vector<double>  spl(string str);

//not used
//void readCSV(istream &input, vector< vector<string> > &output);

#endif //FILE_H
