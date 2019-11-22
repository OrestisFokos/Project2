#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include "calculations.h"
#include "brute_force.h"

class Hypercube
{
    int number;    // No. of buckets

    // Pointer to an array containing buckets
    vector<vector<new_type>*> *table;
public:
    Hypercube(int V);  // Constructor

    ~Hypercube();
    // inserts a key into hash table
    void insertItem(vector<new_type>* p, int index);

    // deletes a key from hash table
    void deleteItem(int index);


    void displayHypercube();

    void displayNeighbors(int* N);

    vector<dist_id> min_distances_HC(Hash **T,vector<vector<new_type>> query);
};

void printMinDistances(vector<dist_id> v_dist_id);

int* neighbors(int* queryTag,int d_hC); // farray gives queryTag
int* fArray(Hash **T,vector<new_type> p,vector<double> **s,int d_hC);
int f_to_int(int* f,int d_hC); // d_hypercube
int binaryStringToDec(string);

#endif //HYPERCUBE_H