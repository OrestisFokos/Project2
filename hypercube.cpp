#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include "calculations.h"
#include "hashTable.h"
#include "hypercube.h"
#include "brute_force.h"


using namespace std;

int n = 1000;
int d_hC = (int) ceil(log2(n)); // works for positive numbers
int probes = 8;
int MM = 10;
extern int L,tableSize;
extern vector<double> **s;

Hypercube::Hypercube(int b) // b = 2^d_hC = n
{
    this->number = b;
    table = new vector<vector<new_type>*> [number]; // new vector<new_type>*[number]
}

Hypercube::~Hypercube(){
    delete[] table;
}

void Hypercube::insertItem(vector<new_type>* p, int index) // index = f
{
    table[index].push_back(p);
}

void Hypercube::deleteItem(int index) // index = f
{
    // delete vector in table[index]

    if (table[index].empty() == 0){
        table[index].clear();
        table[index].shrink_to_fit();
    }

}

// function to display hash table
void Hypercube::displayHypercube() {
    for (int i = 0; i < number; i++) {
        cout << i;
        for (auto x : table[i] ) {
            for (int j = 0; j < table[i].size(); j++)
               if (x[j].empty() == 0 ) cout << " " << x[j][0]; // print point's id
        }
        cout << endl;
    }
}

void Hypercube::displayNeighbors(int* N){
    for (int i = 0; i < d_hC; i++){
        if (table[N[i]].empty() == 0){
            cout<<N[i]<<endl;
           cout<<"Neighbors: "<<(*(table[N[i]][0]))[0]<<endl; // id
        }
    }
}

vector<dist_id> Hypercube::min_distances_HC(Hash **T,vector<vector<new_type>> query){
    double temp_dist;
    int temp_id;
    vector<dist_id> v_dist_id;

    for (int i = 0; i < query.size(); i++){
        temp_dist = -1.0;
        temp_id = -1;
        dist_id distAndId;
        int *N = new int[d_hC];
        N = neighbors(fArray(T,query[i],s,d_hC),d_hC);
        for (int j = 0; j < probes; j++){
            for (int x = 0; (x<table[N[j]].size() && x < MM); x++) {
                double dist = distance(query[i], table[N[j]][x][0], "manhattan");
                if (x == 0 && temp_dist == -1.0) {
                    temp_dist = dist;
                    temp_id = table[N[j]][x][0][0];
                } else if (temp_dist > dist) {
                    temp_dist = dist;
                    temp_id = table[N[j]][x][0][0];
                }
            }
        }
        delete[] N;
        distAndId.dist = temp_dist;
        distAndId.id = temp_id;
        if(temp_dist > -1.0) v_dist_id.push_back(distAndId); // in case of empty neighbors
    }
    return v_dist_id;
}

void printMinDistances(vector<dist_id> v_dist_id){
    for (int i = 0; i < v_dist_id.size(); i++){
        cout<<"query: "<<i<<" has min distance with point: "
                << v_dist_id[i].id << " distance: "<< v_dist_id[i].dist<<endl;
    }

}

// array that stores Hypercube's table index of query's neighbors
int* neighbors(int* queryTag,int d_hC){
    string query_str;
    for (int i = 0; i < d_hC; i++){
        query_str.push_back( queryTag[i] + '0' );
    }
    string *str = new string[d_hC];
    int *N = new int[d_hC];
    for (int i = 0; i<d_hC; i++){
        str[i] = query_str;  // query tag has size of d_hC
        str[i][i] = (query_str[i] == '1') ? '0' : '1';
        N[i] = binaryStringToDec(str[i]);
    }
    delete[] str;
    return N;
}

int binaryStringToDec(string binary){
    int value = 0;
    int indexCounter = 0;
    for(int i = binary.length()-1; i>=0 ; i--){

        if(binary[i]=='1'){
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}

// check only in first hashtable,give **s and use first table to create gL+1 up tp gd_hC
int* fArray(Hash** T,vector<new_type> p,vector<double> **s,int d_hC){ //d_hypercube
    int* f = new int[d_hC]; // exists when scope ends
    int j;
    for (int i = 0; i < d_hC; i++) {
        if (i>=L) { f[0] = (*T)[0].check_f(p,s[i]); }
        else{ f[i] = (*T)[i].check_f(p, s[i]); }
    }
    return f;
}

int f_to_int(int* f,int d_hC){
    string str;
    for (int i = 0; i < d_hC; i++){
        str.push_back(f[i] + '0'); //convert to char
    }
    //convert binary value to decimal
    return binaryStringToDec(str);
}
