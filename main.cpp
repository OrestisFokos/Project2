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
        // if (string(argv[i]) == "-q") query_file = string(argv[i + 1]);
        // if (string(argv[i]) == "-k") k = atoi(argv[i + 1]);
        // if (string(argv[i]) == "-L") L = atoi(argv[i + 1]);
        if (string(argv[i]) == "-o") output_file = string(argv[i + 1]);
    }
    else{
        if (string(argv[i]) == "-d") input_file = string(argv[i + 1]);
        // if (string(argv[i]) == "-q") query_file = string(argv[i + 1]);
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
  input = read_input_points(input_file);
  cout<<"read whole input file"<<endl;
  //calculate avg_nn_distance for all points in dataset, if you wish to skip this step comment below lines
  vector<dist_id> brute_nn_points;
  double avg_nn_distance;
  //brute_nn_points = brute_min_distance_all(All,avg_nn_distance,distance_type);
  cout<<"before s init"<<endl;

  S_init();

  vector<vector<new_type>> curves_1;
  vector<vector<new_type>> curves_2;
  for (int i = 0; i<20; i++){
      curves_1.push_back(All[i]);
  }
  for (int i = 20; i<40; i++){
      curves_2.push_back(All[i]);
  }

  cout<<"dynamic distance: "<<min_C(curves_1,curves_2,20,20)<<endl;

  // Hypercube H(pow(2,d_hC));
  // for (int i = 0; i< All.size(); i++){
  //     int *f_temp= fArray(&hashTables,All[i],s,d_hC);
  //     H.insertItem(&(All[i]),f_to_int(f_temp,d_hC));
  //     delete[] f_temp;
  // }

  All = input->dimensions;



  clock_t begin;
  clock_t end;
  double elapsed_secs;


  //reading points
  begin = clock();
  InputPoints *input;
  vector<vector<new_type>> All;
  input = read_input_points(input_file);
  All = input->dimensions;
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time for reading point input : "<<elapsed_secs<<endl;

  //reading curves
  begin = clock();
  InputCurves * input_curves;
  input_curves = read_input_curves("dataset-curves/trajectories_dataset_small.csv");
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time for reading curve input : "<<elapsed_secs<<endl;



  cout<<"read whole input file"<<endl;

  S_init();


  Hash * hashTables;
  hashTables = create_hashTables(&All);
  vector <dist_id> ann_complete_results;

  cout<<"created hashTables"<<endl;


/*
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




  All.erase (All.begin());  //den kserw an xreiazetai, to kanw gia na vgalw tin grammi pou leei "vectors"
  int K = 4;
  // to random K prepei na einai pointers se NEA simeia
  vector <vector<new_type> *> * random_K;
  random_K = random_initialization(&All, K);
  cout<<"teleiwse to random_initialization"<<endl;

  cout<< "RANDOM K "<<random_K->at(0)->at(1)<<endl;

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
  vector<vector<new_type>> test;
  test.push_back(All.at(0));
  test.push_back(All.at(1));
  test.push_back(All.at(2));
  test.push_back(All.at(3));

  lloyds_assignment(&All,&test);


  //delete random_K;

  delete random_K;
  delete input;
  delete input_curves;
  S_delete();
  delete[] hashTables;



  return 0;

}
