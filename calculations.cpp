#include <iostream>
#include "calculations.h"
#include <chrono>
#include <random>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

double w = 4; // global w


int d = 20;
int k = 4;
int L = 5;
double delta = 0.00001;
extern int n;
int tableSize = n/8;
long long m = 2^32 - 5;
long long M = 2^32/k;


double min_C(vector< vector<new_type> > p, vector< vector<new_type> > q, int x, int y){ // dtw
    double **C = new double*[x]; // define C
    for (int i = 0; i < x; i++){
        C[i] = new double[y];
    }

    vector<new_type> V; // point of curve with all 0's
    for (int i = 0; i < p[0].size(); i++){
        V.push_back(0.0);
    }
    if (p.size() < q.size()){ // make both curves m-dimension
        for (int i = 0; i < q.size() - p.size(); i++){
            p.push_back(V);
        }
    }
    else{
        for (int i = 0; i < p.size() - q.size(); i++){
            q.push_back(V);
        }
    }

    for (int i = 0; i < x; i++){ // bottom-up
       for (int j = 0; j < y; j++){
           if (i == j && i == 0){
                C[0][0] = distance(p[i],q[i],"euclidean");
           }
           else if( j > 0 && i == 0 ){
               C[0][j] = C[0][j-1] + distance(p[0],q[j],"euclidean");
           }
           else if( i > 0  && j == 0){
               C[i][0] = C[i][0] + distance(p[i],q[0],"euclidean");
           }
           else{
               double min = C[i-1][j];
               if (min > C[i-1][j-1]) min = C[i-1][j-1];
               if (min > C[i][j-1]) min = C[i][j-1];
               C[i][j] = min + distance(p[i],q[i],"euclidean") ;
           }
       }
    }

    for (int i = 0; i < x; i++){// delete C
           delete[] C[x];
    }
    delete[] C;
}

long long modularPow(long long m,int d, long long M) // m^(d-1) = m^(d-1)/2 * m(d-1)/2
{
    long long res = 1;      // Initialize result

    m = m % M;  // Update m if it is more than or
    // equal to p

    while (d > 0)
    {
        // If d is odd, multiply m with result
        if (d % 2 == 1)
            res = (res*m) % M;

        // m must be even now
        d/= 2;
        m = (m*m) % M;
    }
    return res;
}

vector<double> randomVector(){

    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution(0.0, delta);

    int d = 10; // dimension
    vector<double> s;
    double sum = 0.0;
    for (int i=0; i<d; ++i) { //generate vector s in (0,w)
        double x;
        while ( (x = distribution(generator)) == 0.0){ // [0,w)
            x = distribution(generator);
        }
        s.push_back(x); // x in
        sum ++; // use it for normalization
    }

    // l2-normalization
    sum = sqrt(sum);
    for (vector<double>::iterator it = s.begin() ; it != s.end(); ++it) {
        *it = (*it)/sum;
    }

    return s;

}

double randomNumber(double x_value, double y_value){ // uniform distribution [x_value,y_value)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution (x_value, y_value);
    return distribution(generator);
}


//calculate ai and store them in a_vector,free a_vector after usage
vector<new_type> a_calculation( vector<new_type> p, vector<double> r){
    vector<new_type> a;
    for (auto it = p.begin(); it != p.end(); ++it){
        auto it2 = r.begin();
        if ( it == p.begin() )it++; it2++;
        a.push_back( (*it - *it2)/w );
        it2++;
    }
    return a;
}

double distance(vector<new_type> p,vector<new_type> q,string distance_type){ // vector<new_type>, when needed cast to double
    int k;
    if (distance_type == "manhattan") k = 1;
    else if (distance_type == "euclidean") k = 2;
    else if (distance_type == "k-norm"){
                 k = stoi(distance_type);
           }

    double sum = 0.0;
    for (int i = 0; i < p.size(); i++){
        sum += pow ( (double) abs( p[i] - q[i] ), (double) k );
    }

    return pow(sum, 1.0/(double) k);

}

long long h_calculation(vector<new_type> a){
    long long sum = 0;
    for (int i = 0; i < a.size(); i++){
        sum += ( ((int) a[i] % M) * modularPow(m,d-1-i,M) ) % M; // modularPow returns 1 in case of d-1 = 0
        // sum does not provoke overflow since d*M << 2^64 (see dataset,d < 2^8)
    }

    return sum % M;
}


int binarytoDec(new_type *arrbin) {
    int multiplier = 1;
    int bin = 0;
    for (int i = 0; i < 32; i++) {
        bin += (multiplier * arrbin[i]);
        multiplier *= 2;
    }
    return bin;
}

int decToBinaryConcat(vector<new_type> h_f){
    new_type binaryNum[32];
    int i = 0;
    new_type s = 32/k;
    for (auto it = h_f.begin(); it!= h_f.end(); ++it){

        while( (int) *it > 0 ){
            binaryNum[i] =(int) (*it) %  2;
            *it = (*it)/2;
            i++;
        }

        while ( i < s  ){
            binaryNum[i++] = 0;
        }
        s = s + 32/k;

    }
    for (int j = i; j<32; j++){ binaryNum[j] = 0; }
    return binarytoDec(binaryNum);
}

vector<new_type> vector_padding(vector<vector<new_type>> p){
   int max_points = 200; // in trajectories dataset second character
   new_type max = p[0][0];

   vector<new_type> v;
   for (int i = 0; i < p.size(); i++){ // find max
     for(int j = 0; j < p[i].size(); j++){
        if (max < p[i][j]) p[i][j] = max + 0.5;
     }
   }

   for (int i = p.size(); i < max_points; i++){ // create vector v to hash
     for(int j = 0; j < p[i].size(); j++){
        v.push_back(p[i][j]);
     }
   }
   return v;
}

double delta_calc(vector< vector<vector<new_type>> > P){
  double dist,dist2;
  dist2 = 0;

  for(int i = 0; i < P.size(); i++){
    dist = 0;
    for(int j = 0; j < P[i].size() - 1; j++){
      dist += distance(P[i][j],P[i][j+1],"euclidean");
    }
    dist = dist / (P[i].size() - 1);
    dist2 += dist;
  }
  return dist2 = dist2 / (P.size());
}

vector<vector<new_type>> grid_points(vector<vector<new_type>> p,vector<double> t){ //create grid_curve,t is randomVector()
    //find a_i
    vector<vector<new_type>> grid_curve;
    vector<new_type> a;

    for (int i = 0; i < p.size(); i++){
        int dup = 0;
        for(int j = 0; j<p[i].size(); j++){
            a.push_back((delta * round(t[i]-p[i][j]))); // create a_0*δ...a_j*δ using manhattan ( round(t-p) )
        }

        //cant have duplicates
        for (int x = 0; x < grid_curve.size(); x++){
            if (grid_curve[x] == a) { dup = 1; break; }
        }
        if (dup == 0) grid_curve.push_back(a); // add grid's point to create grid_curve,concat

        a.clear();
        a.shrink_to_fit();
    }
    //padding
    return grid_curve;
}
