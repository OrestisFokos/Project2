#ifndef FILE_H
#define FILE_H

using namespace std;

typedef float new_type;


typedef struct InputPoints{
  vector <string> ids;
  vector < vector<new_type> > dimensions;
}InputPoints;

typedef float new_type;

InputPoints * read_input_points(string filename);

#endif //FILE_H
