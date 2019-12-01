#ifndef RANGE_SEARCH_H
#define RANGE_SEARCH_H
#include <stdlib.h>

typedef double new_type;

vector<dist_id> range_search (
  Hash * T,
  vector<double> *s,
  vector<new_type> query,
  double range,
  string distance_type);


vector<vector<dist_id>> range_search_complete(
  Hash * hashTables,
  vector<double> **s,
  vector<vector<new_type>> * queries,
  double range,
  string distance_type);





#endif //RANGE_SEARCH_H
