//picture.cpp
//Forrest Hicks

#include "picture.h"

void picture::assign_address(string s) {
	address = s;
}

void picture::assign_tag(string s, int tag_num) {
	if(tag_num > 5 || tag_num < 1)		//can't have more than 5 tags
		throw invalid_argument("Error: Bad tag(Your index file may have become corrupted, try clearing it)");

	tags[tag_num-1] = s;
}

vector<string> picture::get_tags() {
	return tags;			//acquire the tags from the picture object for use
}

string picture::get_tag(int tagnum){
	return tags[tagnum-1];
}

string picture::get_address() {
	return address;				//acquire the url from the picture object for use
}

void picture::save(ofstream& file) { //saves the address then the tags separated by white space

	file << address << " ";			 //then puts a semicolon at the end to signify when a new picture
									 //object is needed
	for(int i=0; i<5; i++) {
		if(tags[i] != UNASSIGNED) {
			file << tags[i] << " ";
		}
	}
		
	file << ";" << endl;
}
