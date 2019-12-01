#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

typedef double new_type;

typedef struct dist_id *D;

struct dist_id{
    double dist;
    int id;
    double time;
};

double distance(vector<new_type> p,vector<new_type> q,string distance_type);

dist_id brute_min_distance(vector<new_type> query, vector<vector<new_type>> All, string distance_type);
vector <dist_id> brute_min_distance_all(vector<vector<new_type>> All, double & avg_nn_distance, string distance_type); //epistrefei vector me min distance gia kathe point
#endif //BRUTE_FORCE_H
