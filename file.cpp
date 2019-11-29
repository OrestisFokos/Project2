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


InputCurves * read_input_curves(string filename){

	ifstream file;
	file.open(filename.c_str());
	if ( file.fail() ){
		cout << "Couldn't open the file!" << endl;
		cerr << "Error: " << strerror(errno);
		exit(-1);
	}

	int i;
	int ncurves = 0;
	string line;
	vector<string> ids;
	vector<tuple <new_type,new_type> > output;
	InputCurves * Curves = new InputCurves;
	// diavazoume prwta tin prwti grammh tin opoia petame
	getline(file,line);	//diavazoume to arxeio grammi grammi
	while (file.peek() != EOF){
		getline(file,line);	//diavazoume to arxeio grammi grammi
		ncurves++;
		output.clear();
		string id;
		int word;
		stringstream s(line);	//xwrizei to string gia epeksergasia meta
		s>>id;
		Curves->ids.push_back(id);

		// twra vlepw posa simeia akolouthoun gia diavasma
//		s>>word;

	while(s>>word){
//		output = s;
			cout<<"printing what is saved in s: " << s.str() <<endl;
	//	output.push_back(word);	//gemizw to vector me ena dimension th fora
}

	// //debug print
	// for (int i=0;i<output.size();i++){
	// 	cout<<output.at(i)<<endl;
	//
	// }

		//Points->dimensions.push_back(output);

		// an theloume na stamatisoume to diavasma prin to telos tou arxeiou
	 if  (ncurves == 2)
			break;


	}

	file.close();
	return Curves;



}
