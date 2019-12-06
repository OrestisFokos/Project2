#include <iostream>
#include <iterator>
#include <vector>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime> //gia xronometrisi
#include <cmath>
#include "file.h"
#include "brute_force.h"
#include "hashTable.h"
#include "calculations.h"	//gia na exw to extern int tableSize
#include "hypercube.h"
#include "ann.h"
//PROSFATA
#include "range_search.h"
#include "initialization.h"
#include "assignment.h"

using namespace std;

extern int tableSize;
extern vector<double> **s;
extern int n;
extern int k;
extern int d;
extern int d_hC;
extern int probes,L,MM;


int main(int argc, char *argv[]){


  string input_file ;
  string query_file;
  string output_file;
  for (int i=1;i<argc-1;i++){
    if (string(argv[0]) == "lsh") {
        if (string(argv[i]) == "-d") input_file = string(argv[i + 1]);
         if (string(argv[i]) == "-q") query_file = string(argv[i + 1]);
        // if (string(argv[i]) == "-k") k = atoi(argv[i + 1]);
        // if (string(argv[i]) == "-L") L = atoi(argv[i + 1]);
        if (string(argv[i]) == "-o") output_file = string(argv[i + 1]);
    }
    else{
        if (string(argv[i]) == "-d") input_file = string(argv[i + 1]);
        if (string(argv[i]) == "-q") query_file = string(argv[i + 1]);
        // if (string(argv[i]) == "-k") k = atoi(argv[i + 1]);
        // if (string(argv[i]) == "-M") MM = atoi(argv[i + 1]);
        // if (string(argv[i]) == "-probes") probes = atoi(argv[i + 1]);
        if (string(argv[i]) == "-o") output_file = string(argv[i + 1]);
    }
  }

  string distance_type;
  distance_type = "manhattan";
  // READING INPUT

  if (input_file.empty()){
    cout<< "Please enter input_file path"<<endl;
    cin>>input_file;
  }
  /*input = read_input_points(input_file);
  cout<<"read whole input file"<<endl;
  //calculate avg_nn_distance for all points in dataset, if you wish to skip this step comment below lines
  vector<dist_id> brute_nn_points;
  double avg_nn_distance;
  //brute_nn_points = brute_min_distance_all(All,avg_nn_distance,distance_type);
  cout<<"before s init"<<endl;*/

  S_init();





  clock_t begin;
  clock_t end;
  double elapsed_secs;


  //reading points
  InputPoints *input;
  vector<vector<new_type>> All;
  input = read_input_points(input_file);
  All = input->dimensions;


  Hash * hashTables;
  hashTables = create_hashTables(&All);
  vector <dist_id> ann_complete_results;



/*
// RANGE SEARCH, NOT USED, BUT CORRECT!
  int range = 4000;
  vector<dist_id> rr;
  cout<<"RANGE SEARCH"<<endl;

  for (int i=0; i <queries.size();i++){

    rr = range_search(hashTables,s[0],queries.at(i),range, distance_type);
//    cout<<"number of points in range = "<< rr.size()<<endl;
    for (int j=0; j<rr.size();j++){
//      cout<<"id "<<rr.at(j).id<<" dist = "<<rr.at(j).dist<<endl;
    }
  }

  vector<vector<dist_id>> rr_total;
  rr_total = range_search_complete(hashTables,s,&queries,range, distance_type);
*/




  All.erase (All.begin());  //den kserw an xreiazetai, to kanw gia na vgalw tin grammi pou leei "vectors"

  vector<vector<new_type>> test;
  test.push_back(All.at(0));
  test.push_back(All.at(1));
  test.push_back(All.at(2));
  test.push_back(All.at(3));

  delete input;
  S_delete();
  delete[] hashTables;

  /* CURVE READ INPUT */

  // InputCurves* AllCurves;
  // AllCurves = read_input_curves("./curves_dataset/trajectories_dataset_small.csv");
  // cout<<"curves testing: id of first curve is = "<< AllCurves->ids.at(0) <<endl;
  // cout<<"curves testing: prwto dimension tou prwtou point tou prwtou curve =  "<<AllCurves->dimensions.at(0).at(0).at(0)<<endl;  //prwto dimension tou prwtou point tou prwtou curve
  // delete AllCurves;

  /* creating K empty clusters and using random initialize to assing their centroids */

  int K = 4;
  vector <vector<new_type> *> * random_K_centroids;
  // na dw an to random_init tha prepei na einai gia uparxonta h nea simeia
  random_K_centroids = random_initialization_point(&All, K);
  //twra sto random_K exoume ena ptr se vector me centroids,
  //diladi ena vector <vector <new_type> * > *

  vector<PointCluster> clusters =  create_clusters_point(K);
  for (int i=0;i<K;i++){
    clusters.at(i).centroid = *( random_K_centroids->at(i) );
  }
  cout<<endl<<"We have "<<K<<" clusters. Now assigning points to clusters.."<<endl;
  /* as kanoume twra assign ola ta point se clusters*/

  // ftiaxnoume hash table megalou megethous me prwto arithmo apo bucket
    Hashtable_points hp(739);
    for (int i=0;i<All.size();i++){
      lloyds(&(All.at(i)),&clusters,&hp);
    }


  /* random centroids assigned correctly */



// test some points, to see their clusters
cout<<"lets see some of the points' clusters"<<endl;
  for(int i=0;i<30;i++){
  cout<< hp.displayHashCluster(All.at(i))<<" ";
}
for(int i=140;i<160;i++){
cout<< hp.displayHashCluster(All.at(i))<<" ";
}
for(int i=200 ;i<220;i++){
cout<< hp.displayHashCluster(All.at(i))<<" ";
}

for(int i=0;i<K;i++){
  cout<< "Cluster "<<i<<" has "<<clusters.at(i).objects.size()<<" points."<<endl;
}


  /* end of hashtable points debug */


  delete random_K_centroids;

  return 0;

}
