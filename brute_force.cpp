#include <iostream>		// isws den xreiazetai
#include <tgmath.h>		// gia to sqrt
#include <cmath>		//gia to pow()
#include <ctime> //gia xronometrisi
#include <vector>
#include "calculations.h"
#include "brute_force.h"
using namespace std;

// brute force NN gia ola ta stoixeia tou All, episrefei kai to avg_nn_distance
 vector<dist_id> brute_min_distance_all(vector<vector<new_type>> All, double & avg_nn_distance, string distance_type){
	vector<dist_id> min_distances(All.size());
	double temp_min;
	double d;
	int temp_id;
	avg_nn_distance = 0.0;
//arxikopoiisi
  min_distances.at(0).dist = distance(All.at(0),All.at(1),distance_type);
  min_distances.at(0).id = All.at(1).at(0);

	for (int i=1;i<All.size();i++){
		min_distances.at(i).dist = distance(All.at(i),All.at(0),distance_type);
        min_distances.at(i).id = All.at(0).at(0);
	}


	for (int i=0;i<All.size();i++){	//for every point find min_distance
		for (int j=i+1;j<All.size();j++){
				d = distance(All.at(i),All.at(j),distance_type);
				if (d < min_distances.at(i).dist){
					temp_min = d;
					temp_id = All.at(j).at(0);
					// nearest neighbor tou I einai o J
				}
				if (d < min_distances.at(j).dist){
					min_distances.at(j).dist = d;
					min_distances.at(j).id = All.at(i).at(0);
				}
		}
		min_distances.at(i).dist = temp_min;
		min_distances.at(i).id = temp_id;
	//	cout<<min_distances.at(i)<<endl;
		avg_nn_distance += min_distances.at(i).dist;
	}

	avg_nn_distance = avg_nn_distance / All.size();

	return min_distances;
}


// brute force NN gia to query, apo ola ta simeia tou All.
dist_id brute_min_distance(vector<new_type> query, vector<vector<new_type>> All, string distance_type){
	double temp_min;
	int temp_id;
  clock_t begin = clock();
	if(All.size() == 0) {	//bucket is empty
			temp_min = -1;
			exit(0);
	}
	temp_min = distance(query,All.at(0),distance_type);
    temp_id = All.at(0).at(0);
	for (int i=1;i<All.size();i++){
		if(distance(query,All.at(i),distance_type) < temp_min ){
			temp_min = distance(query,All.at(i),distance_type);
			temp_id = All.at(i).at(0);
			//kontinoteros sto query einai to simeio i
		}
	}
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  dist_id min_id;
	min_id.dist = temp_min;
	min_id.id = temp_id;
  min_id.time = elapsed_secs;
	return min_id;
}
