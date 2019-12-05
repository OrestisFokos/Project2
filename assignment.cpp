//assignment.cpp
#include <iostream>
#include "calculations.h"
#include "assignment.h"

//na kanw ta orismata pointers??
void lloyds_assignment(  vector <vector<new_type> > *points, vector <vector<new_type> >* centroids){

  int npoints = points->size();
  int ncentroids = centroids->size();
  if (ncentroids == 0 ){
    cout<<"No centroids at all, can't use lloyds_assignment, exiting."<<endl;
    exit;
  }
  for (int i=0; i<npoints; i++){
    double min_dist = distance( points->at(i),centroids->at(0),"manhattan" );
    string id; // edw tha exw to id tou minimum distance, h ton arithmo tou cluster
    for(int j=0; j<ncentroids;j++){
      if ( distance( points->at(i),centroids->at(j),  "manhattan"  ) < min_dist ){
        min_dist = distance( points->at(i),centroids->at(j) , "manhattan" );
        //update min id also!!
      }
    }
  }
}

void Update(vector<vector<new_type>> cluster, vector<new_type>* centroids){ // need *centroid so i can update inside function
    vector<new_type> new_centroid;
    int cluster_size = cluster.size();
    for (int i = 0; i < cluster_size; i++){
        for (int j = 0; j < cluster[i].size(); j++){
          if (i == 0){
            new_centroid.push_back(cluster[i][j]);
          }
          else{
            new_centroid[j] += cluster[i][j];
          }
        }
    }

    for (int i = 0; i < new_centroid.size(); i++){
      centroids->at(i) = new_centroid[i] / (double) cluster_size;
    }
}

//arg.x is the point that we are searching for its cluster
//find closest centroid so we know x's cluster
int findCluster(vector <vector<new_type>>* centroids, vector<new_type> x){
  int min_i = 0;
  double min_dist =1000000.0;//a big number
  for (int i = 0; i < centroids->size(); i++){
    double dist = distance(x,centroids->at(i),"manhattan");
    if (min_dist < dist){
      min_dist = dist;
      min_i = i;
    }
  }
  return min_i; //cluster is in position min_i
}
