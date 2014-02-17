//browser_window
//Jaiden Gerig
#ifndef BROWSER_WINDOW_H
#define BROSWER_WINDOW_H

#include "GUI.h"  
#include "Graph.h"
#include "Window.h"
#include "picture.h"
using namespace Graph_lib;

struct browser_window : Graph_lib::Window
{
	picture pic;
	browser_window(Point xy, int w, int h, const string& title,string searchterm);
	bool wait_for_button();
	void main_loop();
	int getstate(){return returnstate;};
private:
	bool is_changed=false;
	int returnstate = 2;
	const int gohome = 1;
	const int leave = 0;
	const int rerun = 2;
	int browsestate = rerun;
	int index = 0;
	bool button_pushed;
	
	vector<int> deleted_pics;
	string search;
	vector<string> searchtags;
	vector<string> split(const string& s);
	Vector_ref<Image> ii;
	Text nomatch;
	vector<picture*> namelist;
	vector<picture*> namelist_temp;
	vector<picture*> namelist_main;
	
	Out_box location;
	Out_box tag1;
	Out_box tag2;
	Out_box tag3;
	Out_box tag4;
	Out_box tag5;
	
	bool is_empty(std::ifstream& pFile);
	Button remove_button;
	Button home_button;
	Button exit_button;
	Button next_button;
	Button prev_button;
	
	static void cb_home(Address, Address);
	void home();
	static void cb_exit(Address, Address);
	void exit();
	static void cb_next(Address, Address);
	void next();
	static void cb_prev(Address, Address);
	void prev();
	static void cb_remove(Address, Address);
	void remove();
	
};

#endif