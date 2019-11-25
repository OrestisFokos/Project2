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
