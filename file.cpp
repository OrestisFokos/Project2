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

using point = std::vector<double>;
using curve    = std::vector <point>;
using vec_curve = std::vector<curve>;

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
		cout<<word<<endl;
}

	// //debug print
	// for (int i=0;i<output.size();i++){
	// 	cout<<output.at(i)<<endl;
	//
	// }

		//Points->dimensions.push_back(output);

		// an theloume na stamatisoume to diavasma prin to telos tou arxeiou
	 if  (ncurves == 2)
	 file.close();
			break;
	}
	file.close();

	return Curves;

}


// function to split string of comma separated points to vector
vector<double>  spl(string str){

    vector <double> vec;
    // Returns first token
    char ch[str.size()+1];
    strcpy(ch, str.c_str() );
    char *token = strtok(ch, ",");
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        double d = stod(token);
        vec.push_back(d);
        token = strtok(NULL, ",");
    }
    return vec;
}





// under construction
vec_curve read_input_curves2(string filename){
 	ifstream file;
	file.open(filename.c_str());
	if ( file.fail() ){
		cout << "Couldn't open the file!" << endl;
		cerr << "Error: " << strerror(errno);
		exit(-1);
	}

   string line;
   vec_curve M;
	 getline(file,line);
	 //petame tin prwti grammi pou leei curves

   while ( getline( file, line ) )                   // read a whole line of the file
   {
      stringstream ss( line );                     // put it in a stringstream (internal stream)
      curve row;
      string data;
      point p;
      getline( ss, data, '\t' );
      getline( ss, data, '\t' );
      //petame ta 2 prwta noumera
      while ( getline( ss, data, '\t' ) )           // read (string) items up to a comma
      {
        data.erase(remove(data.begin(), data.end(), '('), data.end());
        data.erase(remove(data.begin(), data.end(), ')'), data.end());
        p = spl(data);
        // thelw na spasw to data pou exei double xwrismenous me kommata
        row.push_back( p);            // use stod() to convert to double; put in row vector
      }
      if ( row.size() > 0 ) M.push_back( row );    // add non-empty rows to matrix

   }
   return M;
}
