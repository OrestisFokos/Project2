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

InputPoints * read_input_points( string filename){

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
		vector<string> ids;
		vector<new_type> output;
		InputPoints * Points = new InputPoints;
		// diavazoume prwta tin prwti grammh tin opoia petame
		getline(file,line);	//diavazoume to arxeio grammi grammi
		while (file.peek() != EOF){
			getline(file,line);	//diavazoume to arxeio grammi grammi
			npoints++;

			output.clear();
			string id;
			new_type word;
			stringstream s(line);	//xwrizei to string gia epeksergasia meta
			s>>id;
			Points->ids.push_back(id);
			while(s>>word){
			output.push_back(word);	//gemizw to vector me ena dimension th fora
		}
			Points->dimensions.push_back(output);
			// an theloume na stamatisoume to diavasma prin to telos tou arxeiou
		 if  (npoints == 100)
				break;


		}

		file.close();
		return Points;
}
