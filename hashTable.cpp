#include<iostream>
#include <list>
#include <array>
#include <random>
#include <chrono>
#include <vector>
#include "hashTable.h"
#include "calculations.h"
using namespace std;

extern int k,d,tableSize,L;
extern double w;
extern long long m,M;
//struct point,add pointer to bucket


vector<double> **s; // size:Lkd*double_size, revaluate g


void S_init(){
    s = new vector<double>*[500];
    for(int i = 0; i < 500; i++){
        s[i] = new vector<double>[500];
    }
}

void S_delete(){
    for(int i = 0; i < 500; i++){
        delete[] s[i];
    }
    delete[] s;
}

Hash* create_hashTables(vector<vector<new_type >>* all){
    Hash *hashTables = new Hash[L];
    for (int i = 0; i < L; i++){
        for (int j = 0 ; j < all->size() ; j++){
            hashTables[i].insertItem( &(all->at(j)), s[i]);
            //hashTables[i].setf();
        }
    }
    return hashTables;
}

/*struct Bucket{ // contains a list of pointers to point
    vector<vector<new_type >*> List;//change: list<Point *> List;
    int f;
}; // use *bucket for reference
 */


Hash::Hash() // constructor
{
    this->number = tableSize;
    table = new Bucket[number]; // array of buckets
    for (int i = 0; i < tableSize; i++){
        table[i].f = -1; // initialize f
    }
}

Hash::~Hash() // constructor
{
   delete[] table; // array of buckets
}

// info about f will be stored only in the first hash table
int Hash::check_f(vector<new_type > p,vector<double> *s){ // check if f already has a value
    int index = hashFunction(p,s);
    if ( table[index].f == -1 ){
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator (seed);
            uniform_int_distribution<int> distribution(0,1);
            table[index].f = distribution(generator);
    }
    return table[index].f;
}

void Hash::insertItem(vector<new_type > *p,vector<double> *s)
{
    int index = hashFunction(*p,s);
    table[index].V.push_back(p);
}

void Hash::deleteItem(vector<new_type > p,vector<double> *s)
{
    // get the hash index of key
    int index = hashFunction(p,s);

    // find the key in (index)th list
    vector < vector<new_type >* > :: iterator i;
    for (i = table[index].V.begin();
         i != table[index].V.end(); i++) {
        if ( **i == p )
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].V.end())
        table[index].V.erase(i);
}

// function to display hash table
void Hash::displayHash() {
    for (int i = 0; i < number; i++) {
        cout << i <<":";
        for (auto x = table[i].V.begin(); x != table[i].V.end(); ++x){
            cout << " " ;
            //for(int i = 0; i < x->size(); i++)
            //{
            if ((*x)->empty() == 0) cout << (**x)[0] << " "; //print id
            //cout << (*x)[i] << " "; //print id
            //}
            //cout << "\n";
        }
        cout << endl;
    }
}

int Hash::hashFunction(vector<new_type > p, vector<double> *s) {  // g
    vector<double> r_vector;
    vector<new_type > h;
    string str;
    if ( s->empty() == 1 ) {
        for (int i = 0; i <k; i++) {
            for(int j = 0; j < d; j++){ //maybe use randomVector()
                r_vector.push_back(randomNumber(0.0,w));
            }
            h.push_back( h_calculation(a_calculation(p,r_vector)) );
            *s = r_vector; //s[i]
            s++;
            r_vector.clear();
            r_vector.shrink_to_fit();
        }
    }
    else{
        for (int i = 0; i <k; i++) {
            h.push_back( h_calculation( a_calculation(p,*(s++)) ) );
        }
    }
    return decToBinaryConcat(h) % tableSize;
}




Bucket *  Hash::getBucket(int index) {
  return &table[index];
}

vector<vector<new_type >*> Hash::get_bucket_contents(int index){   //returns a list of vectors of points in bucket
  Bucket * b;
  b = getBucket(index);
  return b->V;

}
