//assignment.h
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

typedef double new_type;
//LLoyds - slide 10
//range search , LSH (inverse assignment - slide 44)

void lloyds_assignment_point(point * p, vector<PointCluster> Clusters);
void Update(vector<vector<new_type>> cluster, vector<new_type>* centroids);

int findCluster(vector <vector<new_type>>* centroids, vector<new_type> x);
//na ta kanw pointers??

#endif //ASSIGNMENT_H
