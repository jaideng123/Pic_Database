//Esau Galindo
// call is_correct_URL(string web, string file_name) only to return bool value (file_name should include correct extension)
#include <iostream>
#include <string>

string if_correct_get_exten( string web){ // do not call this function it is called by is_correct_URL
	if(web.size()<8){
		// prevents range error
		return "";
		}
		
	string http="";
	string https="";
		for(int x=0;x<7;++x)
			http+=web[x]; 
		for(int x=0;x<8;++x)
			https+=web[x]; 		
	if(!(http=="http://"||https=="https://")){
		//Incorrect URL not http:// or https:// 
		return "";
		}
	//Checks for correct file extension
	string exten="";
	for(int x=web.size()-2;x<web.size();++x)
		exten+=web[x];
	if(exten=="bm"|exten=="BM")
		return exten;	
	exten="";
	for(int x=web.size()-3;x<web.size();++x)
	{
		exten+=web[x];
	}
	if(exten=="gif"||exten=="GIF")
		return "gif";	
	else if(exten=="jpg"||exten=="JPG")
		return "jpg";		
	else if(exten=="bmp"|exten=="BMP")
		return "bmp";
	else if(exten=="pbm"|exten=="PBM")
		return exten;	
	else if(exten=="pgm"|exten=="PGM")
		return exten;
	else if(exten=="png"|exten=="PNG")
		return "png";
	else if(exten=="ppm"|exten=="PPM")
		return exten;
	else if(exten=="xbm"|exten=="XBM")
		return exten;
	else if(exten=="xpm"|exten=="XPM")
		return exten;
	exten="";
	for(int x=web.size()-4;x<web.size();++x)
		exten+=web[x];
	if(exten=="jpeg"||exten=="JPEG")
		return "jpeg";
	else{
		// "File extension was an Incorrect
		return "";
	}
} 

// checks if URL downloads 
//do not call this function it is called by is_correct_URL()
int URL_downloads(string web, string file_name){ 
	int x;
	web = "wget " + web + " -O " + "pics/" + file_name;
	x=system((const char*)web.c_str());
	return x;
	
}

// checks if URL is valid. If so the file is downloaded with new file name
bool is_correct_URL(string web, string file_name){
	int x;
	string exten;
	exten=if_correct_get_exten(web);
	if(exten=="")
	return false;
	for(int y=0;y<exten.size();++y)	//checks that file name has the same extension as the URL
	{
		if(!(file_name[(file_name.size()-exten.size())+y]==exten[y]))
			return false;
	}
	x=URL_downloads(web,file_name);
	if(x==0)
		return true;
	else
		return false;
}