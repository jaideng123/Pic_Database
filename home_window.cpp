//home_window.cpp
//Jaiden Gerig
#include "home_window.h"
#include "error_window.h"
#include <string>
#include "std_lib_facilities_3.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "check_file.h"
#include "readinternet_file.h"
using namespace Graph_lib;
home_window::home_window(Point xy, int w, int h, const string& title)
	:Window(xy,w,h,title),
	browse_button(Point((x_max())-140,0),70,20,"Browse",cb_browse),
	exit_button(Point((x_max())-70,0),70,20,"Quit",cb_exit),
	add_button(Point(670,y_max()-140),70,20,"AddPic",cb_add),
	search_button(Point(335,y_max()-240),70,20,"Search",cb_search),
	clear_button(Point(x_max()-105,y_max()-20),100,20,"CLEAR INDEX",cb_clear),
	search_box(Point(70, y_max()-240),260, 25,"Tags: "),
	location_box(Point(70,y_max()-140),260,25,"Address:"),
	name_box(Point(500,y_max()-140),150,25,"name:"),
	tag1_box(Point(75,y_max()-90),70,20,"tag1_box"),
	tag2_box(Point(210,y_max()-90),70,20,"tag2_box"),
	tag3_box(Point(360,y_max()-90),70,20,"tag3_box"),
	tag4_box(Point(510,y_max()-90),70,20,"tag4_box"),
	tag5_box(Point(660,y_max()-90),70,20,"tag5_box"),
	logo(Point(0,0),"logo.png"),
	add_pic(Point(5,y_max()-160),"ADD PHOTO:"),
	search_pic(Point(5,y_max()-260),"SEARCH BY TAG:(for multiples separate by spaces)"),
	tag_warn(Point(75,y_max()-55),"(Please do not include spaces)"),
	name_warn(Point(500,y_max()-155),"(Remember to add appropriate extension)"),
	clear_warn(Point(x_max()-400,y_max()-30),"(USE ONLY WHEN THE FILE HAS BECOME CORRUPTED)")
{
	add_pic.set_font_size(30);
	attach(add_pic);
	search_pic.set_font_size(30);
	attach(search_pic);
	tag_warn.set_font_size(15);
	attach(tag_warn);
	name_warn.set_font_size(15);
	attach(name_warn);
	clear_warn.set_font_size(15);
	attach(clear_warn);
	attach(logo);
	attach(browse_button);
	attach(exit_button);
	attach(add_button);
	attach(search_button);
	attach(clear_button);
	attach(search_box);
	attach(location_box);//URL/filename address
	attach(name_box);
	attach(tag1_box);//tags
	attach(tag2_box);
	attach(tag3_box);
	attach(tag4_box);
	attach(tag5_box);
	indexfile.open ("index.txt", ios::out | ios::app);
	for(int i=0;i<5;++i)tagadd.push_back("NOTAG");//initializes vector of tags to be added
	main_loop();
}
void home_window::main_loop()
{
	while(homestate != leave)
	{
		wait_for_button();
		if(homestate == gosearch)
		{
			searchstring=search_box.get_string();
			returnstate = 3;//go to search box
			homestate = leave;
		}
		else if(homestate == gobrowse)
		{
			returnstate = 2;//go to browse
			homestate = leave;
		}
		else if(homestate == goadd)
		{
			addpic();
			returnstate = 1;
			homestate = leave;
		}
		else hide();
	}
	hide();
}

bool home_window::wait_for_button()//taken from simple window
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

void home_window::cb_exit(Address, Address pw)
{
	reference_to<home_window>(pw).exit();
}
void home_window::exit()
{
	returnstate = 0;
	homestate = leave;
	button_pushed = true;//for wait_for_button
}

void home_window::cb_browse(Address, Address pw)
{
	reference_to<home_window>(pw).browse();
}
void home_window::browse()
{
	homestate = gobrowse;
	button_pushed = true;
}

void home_window::cb_add(Address, Address pw)
{
	reference_to<home_window>(pw).add();
}
void home_window::add()
{
	homestate = goadd;
	button_pushed = true;
}

void home_window::cb_search(Address, Address pw)
{
	reference_to<home_window>(pw).search();
}
void home_window::search()
{
	homestate = gosearch;
	button_pushed = true;
}

void home_window::addpic()//adds picture to index file
{
	tagadd[0]=tag1_box.get_string();
	tagadd[1]=tag2_box.get_string();
	tagadd[2]=tag3_box.get_string();
	tagadd[3]=tag4_box.get_string();
	tagadd[4]=tag5_box.get_string();
	addstring = location_box.get_string();
	if(addstring == "")
	{
		error_window erwin1(Point(150,150),400,150,"ERROR","NO INPUT");
	}
	else if(addstring.substr(0,4)=="http")
	{
		namestring = name_box.get_string();
		if(is_correct_URL(addstring, namestring))
		{
			string ss;
			ss="pics/"+namestring+" ";
			for(int i=0;i<5;++i)
			{
				if(tagadd[i] != "")
					ss+=" "+tagadd[i];
				else
					ss+=" UNNASSIGNED";
			}
			ss +=" ; ";
			indexfile<<ss<<endl;
		}
		else error_window erwin2(Point(150,150),400,150,"ERROR","BAD URL INPUT");
				
				
	}
	else if(file_is_correct_exten(addstring))
	{
		string ss;
		ss=addstring+" ";
		for(int i=0;i<5;++i)
		{
			if(tagadd[i] != "")
				ss+=" "+tagadd[i];
			else
				ss+=" UNNASSIGNED";
		}
		ss +=" ; ";
		indexfile<<ss<<endl;
	}
	else error_window erwin3(Point(150,150),400,150,"ERROR","BAD INPUT");
	return;
}

void home_window::cb_clear(Address, Address pw)
{
	reference_to<home_window>(pw).clear();
}
void home_window::clear()
{
	ofstream indexclear;
	indexclear.open("index.txt",ios::trunc);
	indexclear.close();
	homestate = leave;
	button_pushed = true;
}
