#ifndef LSH_HASHTABLE_H
#define LSH_HASHTABLE_H
#include <list>
#include <vector>
#include "file.h"
using namespace std;

typedef double new_type;

typedef struct Bucket *bucket; //access from main through *bucket

struct Bucket{ // contains a list of pointers to point
    vector <vector<new_type>*> V;//change: list<Point *> List;

    int f;    // bucket's binary tag
}; // use *bucket for reference*/

void S_init();
void S_delete();

class Hash
{
    int number;    // No. of buckets

    // Pointer to an array containing Buckets
    Bucket *table;
public:
    Hash();  // Constructor

    ~Hash(); // destructor

    int check_f(vector<new_type> p,vector<double> *s);

    // inserts a key into hash table
    void insertItem(vector<new_type> * p,vector<double> *s);

    // deletes a key from hash table
    void deleteItem(vector<new_type> p,vector<double> *s);

    // hash function to map values to key
    int hashFunction(vector<new_type> p, vector<double> *s);

    void displayHash();

    Bucket * getBucket(int index);  // return pointer of bucket number index

    vector<vector<new_type>*> get_bucket_contents(int index);  //returns a vector of pointers to points in bucket, points are vectors of ints

};

Hash* create_hashTables(vector<vector<new_type>>* all);





/* NEW ADDITIONS */
typedef struct point_node{
  point p;
  int cluster;
}point_node;
class Hashtable_points
{
  int nbuckets;    // No. of buckets

  // Pointer to an array containing buckets
  list<point_node> *table;
public:
  Hashtable_points(int nbuckets);  // Constructor
  ~Hashtable_points(); // destructor

  // inserts a key into hash table
  void insertItem(point_node pn);


  // hash function to map values to key
  int hashFunction(point p);

  int displayHash(point p);


};


#endif //LSH_HASHTABLh_
