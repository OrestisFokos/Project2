//assignment.h
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "hashTable.h"

typedef double new_type;
//LLoyds - slide 10
//range search , LSH (inverse assignment - slide 44)

void lloyds(point * p, vector<PointCluster>* Clusters,Hashtable_points* hashTable);
void lloyds_assignment_point(point * p, vector<PointCluster>* Clusters,Hashtable_points* hashTable);
void Update(vector<point *> cluster, point* centroids);

int findCluster(vector<PointCluster> clusters, point x);
//na ta kanw pointers??

#endif //ASSIGNMENT_H
