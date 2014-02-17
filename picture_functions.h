//picture_functions.h
//Forrest Hicks

#ifndef PICTURE_FUNCTIONS_H
#define PICTURE_FUNCTIONS_H

#include "std_lib_facilities_3.h"


//sorts out any pictures that don't have any of the given tags in the vector
vector<picture*> sort_by_tag(vector<picture*>& pics, vector<string>& tags) {
	vector<picture*> sorted_pics;

	for(int i=0; i < pics.size() ;i++) {
		vector<string> pic_tags = pics[i]->get_tags();
		//gets the tags from object "i"
		
		//here is a nested for loops that compares all the tags to each of the picture objects tags
		//if one of the picture objects tags matches the given tags, then it puts that picture object
		//into the "sorted_pics" vector and makes it quit the nested loop by setting "j" and "k" out of their bounds
		for(int j=0; j < pic_tags.size(); j++) {
			for(int k=0; k < tags.size(); k++) {
				if(pic_tags[j] == tags[k]) {
					sorted_pics.push_back(pics[i]);
					j = pic_tags.size();
					k = tags.size();
				}
			}
		}
	}
	return sorted_pics;
}



//gets all the pictures from the data base text file and returns them as a
//vector of picture objects
vector<picture*> get_pictures(ifstream& file) {
	vector<picture*> pics;
	string temp = "NULL";
	
	//the first set of information saved in the file won't have a ";" to detonate a new object
	//so the first object must be created manually
	pics.push_back(new picture);
	file >> temp;
	pics[0]->assign_address(temp);
	file >> temp;
	int i=1;
	while(temp != ";") {	//assigns tags until a semi-colon is reached
		pics[0]->assign_tag(temp, i);
		i++;
		file >> temp;
	}
	
	int j=0;
	int k=1;
	do { //this will keep reading until it reaches the end of the file
		//if a semi-colon is reached then make a new picture object and assign its address
		if(temp == ";") {
			//I made a second if statement here so that it can see if there is anything left
			//in the file without skipping a tag on accident
			if(file >> temp) {
				pics.push_back(new picture);
				j++;
				k=1;
				//I made k=1 here so the tag loop could start adding tags from the first tag slot
				pics[j]->assign_address(temp);
			}
		}
		else {	//otherwise keep adding tags to the latest object
			pics[j]->assign_tag(temp, k);
			k++;
		}
	} while(file >>  temp);
	return pics;
}


//deletes all the the picture pointers so there isn't a memory leak
void clean_up(vector<picture*>& pics) {
	for(int i=0; i < pics.size(); i++) {
		delete pics[i];
	}
}

#endif

//NOTE: the only vectors that need to be cleaned up are vectors made from the get_pictures function
//all the rest are just copied pointers that still point to the same memory of the vectors from get_pictures