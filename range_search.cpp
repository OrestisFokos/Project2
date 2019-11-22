// range_search
// input query, range   returns (neighbor) , distance for all neighbors withing range
#include <iostream>
#include <list>
#include <ctime> //gia xronometrisi
#include "hashTable.h"
#include "calculations.h"
#include "brute_force.h"
#include "range_search.h"

using namespace std;

extern int L;


// range_search gia ena hash table, kai ena query
vector<dist_id> range_search (
  Hash * T,
  vector<double> *s,
  vector<new_type> query,
  double range,
  string distance_type)
  {

  vector<dist_id> in_range;
  int index;
  index = T->hashFunction(query,s);
  vector<vector<new_type>*> vv;
  vv  = T->get_bucket_contents(index);
  //if bucket is empty, we skip this hashTable
  if (vv.size() == 0){
    dist_id d;
    d.dist = -1;
    in_range.push_back(d);
    return in_range;
  }

  vector<vector<new_type>> convertvv;
  vector<new_type> tempv;
  for (int i=0; i <vv.size()  ; i++){
      for(int j=0;j<vv.at(i)->size();j++){
        tempv.push_back(vv.at(i)->at(j));
      }
      convertvv.push_back(tempv);
      tempv.clear();
  }

  new_type dist;
  new_type id;
  dist_id point;
  // na dw oti den metraw distances metaksi onomatwn !!
  for (int i=0; i<convertvv.size();i++){
    dist = distance(query,convertvv.at(i),distance_type);
    if (dist <= range) {
      point.id = convertvv.at(i).at(0);
      point.dist = dist;
      in_range.push_back(point);
    }
  }
  //cout<<"RANGE CHECK DISTANCE = %d, id  =%s\n", distance,id);

  return in_range;
}



/*
epistrefei ena vector me ta in_range tou kathe simeiou
diladi ena vector me vector <dist_id>
*/
vector<vector<dist_id>> range_search_complete(
  Hash * hashTables,
  vector<double> **s,
  vector<vector<new_type>> * queries,
  double range,
  string distance_type)
  {

    vector<vector<dist_id>> in_range_total;
    for (int i=0; i <queries->size();i++){ // for every query
      vector<dist_id> in_range;
      for(int t=0; t< L ; t++ ){ // for every hash table

        in_range = range_search(&hashTables[t],s[t],queries->at(i),range, distance_type);
      }
      in_range_total.push_back(in_range);
    }

      cout<<"number of queries =  "<< in_range_total.size()<<endl;
        cout<<"number of points in range for 1,4,5 =  "<< in_range_total.at(1).size()<< " "<<
        in_range_total.at(4).size()<<" "<<in_range_total.at(5).size()<<endl;
      for (int i=0; i<in_range_total.size();i++){
    //      cout<<"id "<<rr.at(i).id<<" dist = "<<rr.at(i).dist<<endl;
        ;
      }

  return in_range_total;
}
