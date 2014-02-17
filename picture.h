//picture.h
//Forrest Hicks

#ifndef PICTURE_H
#define PICTURE_H

#include "std_lib_facilities_3.h"

class picture {
	private:
		string UNASSIGNED;
		//I created a very odd variable so that the user can easily accidentally assign unassigned to a tag
		vector<string> tags;
		string address;
		
	public:
		picture() : UNASSIGNED(""), address("NULL") {
			tags = {UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED};
		}
		void assign_address(string s);		//assign an address
		void assign_tag(string s, int tag_num); //give a string to be a tag and a int to save it as that tag number (ie (cats, 2) will save cats to the second tag)
		vector<string> get_tags();		//returns the vector of tags
		string get_tag(int tagnum);
		string get_address();		//returns the pictures address in memory
		void save(ofstream& file);		//pass this function a output file by value for the picture to save itself
		
};

#endif