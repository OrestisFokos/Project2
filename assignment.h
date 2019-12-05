//assignment.h
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

typedef double new_type;
//LLoyds - slide 10
//range search , LSH (inverse assignment - slide 44)

int lloyds_assignment_point(point * p, vector<PointCluster> Clusters);
void Update(vector<point *> cluster, point* centroids);

int findCluster(vector<PointCluster> clusters, point x);
//na ta kanw pointers??

#endif //ASSIGNMENT_H
