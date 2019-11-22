#ifndef ANN_H
#define ANN_H

typedef float new_type;

dist_id ann(Hash * T,vector<double> *s, vector<new_type> query, string distance_type);
vector<dist_id> ann_complete(Hash * hashtables, vector<double> **s, vector<vector<new_type>> * queries, string distance_type);


#endif //ANN_H
