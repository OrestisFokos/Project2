//Random Initialization
#include <iostream>
#include <chrono>
#include <random>
#include "file.h" // apla gia to typedef

// randomly pick K points as centroids.



/* struct me ta centroids?? pou tha exei ena vector apo pointer se  points,
 diladi ena vector< vector<new_type> *>


*/

vector <vector<new_type> *> *  random_initialization (
  vector<vector<new_type>> * Dataset,
  int K)
{
  // first we should figure out how many points we have in our dataset
  int sizeofdataset = Dataset->size();
  cout<<"sizeofdataset = "<< sizeofdataset<<endl;
  // na dw oti den metraw kai tuxon plirofories grammenes prin ta points
  if (Dataset->size() == 0){
    cout<< "Dataset is empty!"<<endl;
    exit(-1);
  }

  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  uniform_real_distribution<double> distribution(0, K-1); //thelw na epilegw arithmous apo 0 ews K-1
  int dimensions = Dataset->at(1).size(); // vriskw poses diastaseis exoun ta simeia
  vector <vector<new_type> *> * centroids = new vector< vector<new_type> * > ;

  cout<<"mesa sto function, prin to for"<<endl;

  for(int i=0;i<K;i++){
    int random_index = distribution(generator);
    (*centroids).push_back( & ( Dataset->at(random_index) ) );
    cout<<"mesa sto function, mesa sto for"<<endl;

  }
  cout<<"telos to for"<<endl;
  cout<<centroids->at(0)->at(0)<<endl;
  cout<<"vgainw apto func"<<endl;



  return centroids;
}
