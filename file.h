#ifndef FILE_H
#define FILE_H
#include <tuple>
using namespace std;

typedef float new_type;




typedef struct InputPoints{
  vector <string> ids;
  vector < vector <new_type> > dimensions;
}InputPoints;

//kathe curve einai vector apo tuples me x,y diastaseis k exei k ena curve id
typedef struct InputCurves{
  vector <string> ids;
  vector < vector <tuple <new_type,new_type> > > dimensions;
}InputCurves;

typedef float new_type;

InputPoints * read_input_points(string filename);

InputCurves * read_input_curves(string filename);

#endif //FILE_H
