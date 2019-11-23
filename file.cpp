#include <iostream>
#include <iterator>
#include <vector>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime> //gia xronometrisi
#include "file.h"
#include "brute_force.h"
#include "hashTable.h"
#include "calculations.h"	//gia na exw to extern int tableSize
using namespace std;

extern int tableSize;

vector<vector<new_type>> read_input_to_vector( string filename){

		ifstream file;
		file.open(filename.c_str());
		if ( file.fail() ){
			cout << "Couldn't open the file!" << endl;
			cerr << "Error: " << strerror(errno);
			exit(-1);
		}

		int i;
		int npoints = 0;
		string line;
		vector<vector<new_type>> All;
		vector<new_type> output;
		while (file.peek() != EOF){
			getline(file,line);	//diavazoume to arxeio grammi grammi
			npoints++;
			//cout<<"read line "<<npoints<<endl;
			output.clear();
			new_type word;
			stringstream s(line);	//xwrizei to string gia epeksergasia meta
				while(s>>word){
				output.push_back(word);	//gemizw to vector me ena dimension th fora
			}
			All.push_back(output);
			// an theloume na stamatisoume to diavasma prin to telos tou arxeiou
		 if  (npoints == 100)
				break;


		}

		file.close();

		return All;
}
