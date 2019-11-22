// ANN
// input query,  returns best (neighbor) , distance
#include <iostream>
#include <list>
#include<bits/stdc++.h> //gia to INT_MAX
#include <ctime> //gia xronometrisi
#include "hashTable.h"
#include "calculations.h"
#include "brute_force.h"

using namespace std;

extern int L;

// ann gia ena hash table, kai ena query
dist_id ann (Hash * T,vector<double> *s, vector<new_type> query, string distance_type){

  int index;
  index = T->hashFunction(query,s);
  vector<vector<new_type>*> vv;
  vv  = T->get_bucket_contents(index);
  //if bucket is empty, we skip this hashTable
  if (vv.size() == 0){
    //cout<<"bucket size = 0"<<endl;
    dist_id d;
    d.dist = -1;
    return d;
  }


  //if bucket contains more than 10L elements, stop searching after 10L
  if ( vv.size() > 10L ) vv.erase(vv.begin()+10L,vv.end());


  vector<vector<new_type>> convertvv;
  vector<new_type> tempv;
  for (int i=0; i <vv.size()  ; i++){
      for(int j=0;j<vv.at(i)->size();j++){
        tempv.push_back(vv.at(i)->at(j));
      }
      convertvv.push_back(tempv);
      tempv.clear();
  }

  dist_id min_bucket_distance = brute_min_distance(query, convertvv,distance_type);
  return min_bucket_distance;
}

//sunoliko ann, gia ola ta hash tables, kai ola ta queries
vector<dist_id> ann_complete (Hash * hashTables, vector<double> **s, vector<vector<new_type>> * queries, string distance_type){
  // initialising min_bucket_distance
  vector <dist_id> min_bucket_distance;
  for(int i = 0; i< queries->size(); i++ ){
    dist_id ann_d = ann(&hashTables[0],s[0], queries->at(i),distance_type);
    if (ann_d.dist < 0) ann_d.dist = INT_MAX;   // if bucket was empty, we haven't found a nearest neighbor so far
    min_bucket_distance.push_back( ann_d );
  }

  for(int j=0;j<queries->size();j++){  //for every query
    clock_t begin = clock();
    for(int i=1;i<L;i++){ //for every hash table
      dist_id ann_distance;
      ann_distance = ann(&hashTables[i],s[i],queries->at(j),distance_type);
      if ( ann_distance.dist < min_bucket_distance.at(j).dist && ann_distance.dist >=0 ){
        min_bucket_distance.at(j).dist = ann_distance.dist;
        min_bucket_distance.at(j).id = ann_distance.id;

      }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    min_bucket_distance.at(j).time = elapsed_secs;
  }

  return min_bucket_distance;
}
