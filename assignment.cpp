//assignment.cpp
#include <iostream>
#include <algorithm>
#include "hashTable.h"
#include "calculations.h"
#include "assignment.h"

void lloyds(point * p, vector<PointCluster>* Clusters,Hashtable_points* hashTable){
  int * nchanges = new int;
  nchanges = 0;
  lloyds_first_assignment_point(p,Clusters,hashTable);
  cout<< "ekana to lloyd first"<<endl;
  do {
    for (int i = 0; i < Clusters->size(); i++) {
      Update(Clusters->at(i).objects, &(Clusters->at(i).centroid));
    }
    lloyds_assignment_point(p,Clusters,hashTable,nchanges);
  }while (nchanges !=0);

}


/* kanw assign to point se ena apo ta clusters, h timh int pou
epistrefei einai o arithmos tou cluster
*/
void lloyds_first_assignment_point(point * p, vector<PointCluster> * Clusters, Hashtable_points* hashTable){

  if (Clusters->size() == 0){
    cout<<"Got no clusters, can't assign anything."<<endl;
    exit(-1);
  }
  int nclusters = Clusters->size();
  double min_dist = distance( *p, Clusters->at(0).centroid, "manhattan" );
  int min_cluster = 0;
  for (int i=1;i<nclusters; i++){
    if (distance( *p, Clusters->at(i).centroid, "manhattan" ) < min_dist){
      min_dist = distance( *p, Clusters->at(i).centroid, "manhattan");
      min_cluster = i;
    }
  }
  point_node pn;
  pn.p = *p;
  pn.cluster = min_cluster;
  hashTable->insertItem(pn);

  // if point not already in cluster then push_back, changes++, remove from previous?
  Clusters->at(min_cluster).objects.push_back(p);
  //debug print
  //cout<< "this point belongs to cluster: "<<min_cluster<<endl;
  //return min_cluster;

}

void lloyds_assignment_point(point * p, vector<PointCluster> * Clusters, Hashtable_points* hashTable, int *nchanges){
  if (Clusters->size() == 0){
    cout<<"Got no clusters, can't assign anything."<<endl;
    exit(-1);
  }

  int nclusters = Clusters->size();
  double min_dist = distance( *p, Clusters->at(0).centroid, "manhattan" );
  int min_cluster = 0;
  for (int i=1;i<nclusters; i++){
    if (distance( *p, Clusters->at(i).centroid, "manhattan" ) < min_dist){
      min_dist = distance( *p, Clusters->at(i).centroid, "manhattan");
      min_cluster = i;
    }
  }

  point_node pn;
  pn.p = *p;
  pn.cluster = min_cluster;

  int previous_cluster;
  previous_cluster = hashTable->displayHashCluster(*p);
  if (min_cluster != previous_cluster){
    (*nchanges) ++;
    hashTable->update(pn);
    // push point in new cluster list, remove from old cluster list
    Clusters->at(min_cluster).objects.push_back(p);

    //svinw apo to proigoumeno cluster to simeio auto me tin std::remove kai tin std::erase
    Clusters->at(previous_cluster).objects.erase(remove(Clusters->at(previous_cluster).objects.begin(), Clusters->at(previous_cluster).objects.end(), p), Clusters->at(previous_cluster).objects.end());

  }


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
  double min_dist = distance(x,clusters[0].centroid,"manhattan");
  for (int i = 0; i < clusters.size(); i++){
    double dist = distance(x,clusters[i].centroid,"manhattan");
    if (min_dist < dist){
      min_dist = dist;
      min_i = i;
    }
  }
  return min_i; //cluster is in position min_i
}
