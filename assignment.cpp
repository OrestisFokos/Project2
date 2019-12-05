//assignment.cpp
#include <iostream>
#include "calculations.h"
#include "assignment.h"

void lloyds(point * p, vector<PointCluster>* Clusters){
  lloyds_assignment_point(p, *Clusters);
  for (int i = 0; i < Clusters->size(); i++) {
    Update(Clusters->at(i).objects, &(Clusters->at(i).centroid));
  }
}

void lloyds_assignment_point(point * p, vector<PointCluster> Clusters  ){

  if (Clusters.size() == 0){
    cout<<"Got no clusters, can't assign anything."<<endl;
    exit(-1);
  }
  int nclusters = Clusters.size();
  double min_dist = distance( *p, Clusters.at(0).centroid, "manhattan" );
  int min_cluster = 0;
  for (int i=1;i<nclusters; i++){
    if (distance( *p, Clusters.at(i).centroid, "manhattan" ) < min_dist){
      min_dist = distance( *p, Clusters.at(i).centroid, "manhattan");
      min_cluster = i;
    }
  }
  //debug print
  cout<< "this point belongs to cluster: "<<min_cluster<<endl;
  return min_cluster;

}


void Update(vector<point *> cluster, point* centroids){ // need *centroid so i can update inside function
    vector<new_type> new_centroid;
    int cluster_size = cluster.size();
    for (int i = 0; i < cluster_size; i++){
        for (int j = 0; j < cluster[i]->size(); j++){
          if (i == 0){
            new_centroid.push_back(cluster[i]->at(j));
          }
          else{
            new_centroid[j] += cluster[i]->at(j);
          }
        }
    }

    for (int i = 0; i < new_centroid.size(); i++){
      centroids->at(i) = new_centroid[i] / (double) cluster_size;
    }
}

//arg.x is the point that we are searching for its cluster
//find closest centroid so we know x's cluster
int findCluster(vector<PointCluster> clusters, point x){
  int min_i = 0;
  double min_dist =1000000.0;//a big number
  for (int i = 0; i < clusters.size(); i++){
    double dist = distance(x,clusters[i].centroid,"manhattan");
    if (min_dist < dist){
      min_dist = dist;
      min_i = i;
    }
  }
  return min_i; //cluster is in position min_i
}
