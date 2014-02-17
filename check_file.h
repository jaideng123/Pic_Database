//Esau Galindo
//This program opens pdf
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include <string>
#include <stdio.h>

bool file_exists_test (const string& name) {
	int size; 
    ifstream f(name.c_str());
    if (f.good()) 
	{	//checks that file is not corrupted
		f.seekg(0, std::ios::end);
		size = f.tellg();	//checks that file is not empty
		f.seekg(0);
		f.close();
		if(size==0)
		{
			return false;
		}
		else
			return true;
    } 
	else 
	{
        f.close();
        return false;
    }   
}

bool file_is_correct_exten(string file_name){

if(file_name.size()<4){ //checks that Filename is long enough prevents range errors
	return false;
	}
	
	if(!file_exists_test(file_name))
		return false;
	//the following verify extentions are correct
	string exten="";
	for(int x=file_name.size()-2;x<file_name.size();++x)
		exten+=file_name[x];
	if(exten=="bm"|exten=="BM")
		return true;
		
	exten="";
	for(int x=file_name.size()-3;x<file_name.size();++x)
		exten+=file_name[x];
	if(exten=="gif"||exten=="GIF")
		return true;	
	else if(exten=="jpg"||exten=="JPG")
		return true;
	else if(exten=="bmp"|exten=="BMP")
		return true;
	else if(exten=="pbm"|exten=="PBM")
		return false;	
	else if(exten=="pgm"|exten=="PGM")
		return false;
	else if(exten=="png"|exten=="PNG")
		return true;
	else if(exten=="ppm"|exten=="PPM")
		return false;
	else if(exten=="xbm"|exten=="XBM")
		return false;
	else if(exten=="xpm"|exten=="XPM")
		return false;

	exten="";
	for(int x=file_name.size()-4;x<file_name.size();++x)
		exten+=file_name[x];
	if(exten=="jpeg"||exten=="JPEG")
		return true;
	else{
		return false;
	}
} 