//home_window.h
//Jaiden Gerig
#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include "GUI.h"  
#include "Graph.h"
#include "Window.h"
using namespace Graph_lib;

struct home_window : Graph_lib::Window
{
	home_window(Point xy, int w, int h, const string& title);
	bool wait_for_button();
	void main_loop();
	string getsearch(){return searchstring;};
	int getstate(){return returnstate;};
private:
	int returnstate = 1;
	const int leave = 0;
	const int rerun = 1;
	const int gobrowse = 2;
	const int gosearch = 3;
	const int goadd = 4;
	int homestate = rerun;
	
	void addpic();
	
	Text add_pic;
	Text search_pic;
	Text tag_warn;
	Text name_warn;
	Text clear_warn;
	
	string searchstring = "NOSEARCH";//sets defaults for searchs
	string addstring = "NOADD";
	string namestring = "NONAME";
	ofstream indexfile;//output stream for adding pics
	vector<string> tagadd;
	bool button_pushed;
	
	Image logo;
	
	In_box search_box;//for search
	In_box location_box;//for add
	In_box name_box;
	In_box tag1_box;
	In_box tag2_box;
	In_box tag3_box;
	In_box tag4_box;
	In_box tag5_box;
	
	Button browse_button;
	Button exit_button;
	Button add_button;
	Button search_button;
	Button clear_button;
	
	static void cb_browse(Address, Address);
	void browse();
	static void cb_exit(Address, Address);
	void exit();
	static void cb_add(Address,Address);
	void add();
	static void cb_search(Address, Address);
	void search();
	static void cb_clear(Address, Address);
	void clear();
};

#endif