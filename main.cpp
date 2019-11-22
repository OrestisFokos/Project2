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
#include "random_initialization.h"
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
        if (string(argv[i]) == "-k") k = atoi(argv[i + 1]);
        if (string(argv[i]) == "-L") L = atoi(argv[i + 1]);
        if (string(argv[i]) == "-o") output_file = string(argv[i + 1]);
    }
    else{
        if (string(argv[i]) == "-d") input_file = string(argv[i + 1]);
        if (string(argv[i]) == "-q") query_file = string(argv[i + 1]);
        if (string(argv[i]) == "-k") k = atoi(argv[i + 1]);
        if (string(argv[i]) == "-M") MM = atoi(argv[i + 1]);
        if (string(argv[i]) == "-probes") probes = atoi(argv[i + 1]);
        if (string(argv[i]) == "-o") output_file = string(argv[i + 1]);
    }
  }

  string distance_type;
  distance_type = "manhattan";
  // READING INPUT
  vector<vector<new_type>> All;

  if (input_file.empty()){
    cout<< "Please enter input_file path"<<endl;
    cin>>input_file;
  }
  All = read_input_to_vector(input_file);
  //calculate avg_nn_distance for all points in dataset, if you wish to skip this step comment below lines
  vector<dist_id> brute_nn_points;
  double avg_nn_distance;
  brute_nn_points = brute_min_distance_all(All,avg_nn_distance,distance_type);


  S_init();


  Hash * hashTables;
  hashTables = create_hashTables(&All);
  vector <dist_id> ann_complete_results;

  // Hypercube H(pow(2,d_hC));
  // for (int i = 0; i< All.size(); i++){
  //     int *f_temp= fArray(&hashTables,All[i],s,d_hC);
  //     H.insertItem(&(All[i]),f_to_int(f_temp,d_hC));
  //     delete[] f_temp;
  // }


  //READING QUERIES
  if (query_file.empty()){
    cout<< "Please enter query_file path"<<endl;
    cin>>query_file;
  }
  ofstream output;
  if (output_file.empty()){
      cout<< "Please enter output_file path"<<endl;
      cin>>output_file;
    }

  vector<vector<new_type>> queries = read_input_to_vector(query_file);
  vector<dist_id> min_dist;
  queries.erase (queries.begin());  // here we delete the first line of queries, since it is the value of R for range check

  clock_t begin;
  clock_t end;
  double elapsed_secs;
  /*//BRUTE NEAREST NEIGHBOR FOR QUERIES

  for (int i=0;i<queries.size();i++){
    min_dist.push_back(brute_min_distance(queries.at(i),All,distance_type));
  }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"TIME FOR BRUTE NEAREST NEIGHBOR FOR QUERIES: "<<elapsed_secs<<endl;


  //ANN DISTANCES FOR QUERIES

  output.open(output_file.c_str());
  auto *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());


  ann_complete_results = ann_complete(hashTables,s,&queries,distance_type);






  //prints
  for(int i=0;i<queries.size();i++){
    cout<< "Query: "<<queries.at(i).at(0)<<endl;
    cout<< "Nearest neighbor: "<<min_dist.at(i).id<<endl;
    cout<< "distance LSH: "<<ann_complete_results.at(i).dist<<endl;
    cout<< "distance True: "<< min_dist.at(i).dist<<endl;
    cout<< "tLSH: " <<ann_complete_results.at(i).time<<endl;
    cout<< "tTrue: "<< min_dist.at(i).time<<endl<<endl;
  }
  output.close();

  // reset cout buffer
  cout.rdbuf(coutbuf);



  // begin = clock();
  // vector<dist_id> v_dist_id = H.min_distances_HC(&hashTables,queries);
  //debug print
  //printMinDistances(v_dist_id);
  // end = clock();
  // elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  // cout<<"Time for hypercube: "<<elapsed_secs<<endl;


  begin = clock();

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
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time for range search: "<<elapsed_secs<<endl;
*/




  int K = 4;
  vector <vector<new_type> *> * random_K;
  random_K = random_initialization(&All, K);
  //twra sto random_K exoume ena ptr se vector me centroids,
  //diladi ena vector <vector <new_type> * > *
  /*
  //debug print
  for(int i=0;i<K;i++){
    cout<<"CLUSTER NUMBER "<< i <<" is : ";
    for ( int j=0 ; j < random_K->at(i)->size(); j++ ) {
      cout<<(random_K->at(i))->at(j)<<" ";
    }
    cout<<endl;
  }

*/


  delete random_K;


  S_delete();
  delete[] hashTables;



  return 0;

}
