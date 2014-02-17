//browser_window.cpp
//Jaiden Gerig
#include "browser_window.h"
#include <string>
#include "std_lib_facilities_3.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "picture.h"
#include "picture_functions.h"
#include "error_window.h"
using namespace Graph_lib;
browser_window::browser_window(Point xy, int w, int h, const string& title,string searchterm)
	:Window(xy,w,h,title),
	nomatch(Point(30,50),"Error: No matches/pictures Please try again"),
	home_button(Point((x_max())-140,0),70,20,"Home",cb_home),
	exit_button(Point((x_max())-70,0),70,20,"Quit",cb_exit),
	next_button(Point((x_max())-70,30),70,20,"Next",cb_next),
	prev_button(Point((x_max())-140,30),70,20,"Prev",cb_prev),
	remove_button(Point((x_max())-70,60),70,20,"Remove",cb_remove),
	location(Point(80,y_max()-80),400,30,"ADDRESS:"),
	tag1(Point((x_max())-120,110),110,20,"tag1:"),
	tag2(Point((x_max())-120,140),110,20,"tag2:"),
	tag3(Point((x_max())-120,170),110,20,"tag3:"),
	tag4(Point((x_max())-120,210),110,20,"tag4:"),
	tag5(Point((x_max())-120,250),110,20,"tag5:")
{
	attach(next_button);
	attach(prev_button);
	attach(home_button);
	attach(exit_button);
	attach(location);//URL/filename address
	attach(tag1);
	attach(tag2);
	attach(tag3);
	attach(tag4);
	attach(tag5);
	search = searchterm;
	ifstream indexin1;
	ifstream indexin2;
	indexin1.open("index.txt");
	if(!is_empty(indexin1))
	{
		namelist_main = get_pictures(indexin1);
		indexin1.close();
		if(search != "ALLTAGS")//gets vector of pictures based on search term
		{
			indexin2.open("index.txt");
			namelist_temp = get_pictures(indexin2);
			searchtags = split(search);
			namelist = sort_by_tag(namelist_temp,searchtags);
		}
		else //open whole file
		{
			indexin2.open("index.txt");
			attach(remove_button);
			namelist = get_pictures(indexin2);
		}
		for(int i=0;i<namelist.size(); ++i)//adds images to vector_ref
		{
			ii.push_back(new Image(Point(10,10),namelist[i]->get_address()));
		}
	}
	else
	{
		error_window erwin1(Point(150,150),400,150,"ERROR","FILE EMPTY");
		returnstate=1;
		hide();
		return;
	}
	main_loop();
}
void browser_window::main_loop()
{
	while(browsestate != leave)
	{
		if(browsestate == rerun)
		{
			if(namelist.size() != 0)
			{
				ii[index].set_mask(Point(10,10),500,500);//restricts picture size
				attach(ii[index]);
				location.put(namelist[index]->get_address());//show picture + tags
				tag1.put(namelist[index]->get_tag(1));
				tag2.put(namelist[index]->get_tag(2));
				tag3.put(namelist[index]->get_tag(3));
				tag4.put(namelist[index]->get_tag(4));
				tag5.put(namelist[index]->get_tag(5));
			}
			else 
			{
				error_window erwin2(Point(150,150),400,150,"ERROR","No Results");
				returnstate=1;
				browsestate = leave;
				hide();
				return;
			}
		}
		wait_for_button();
		if(browsestate == gohome)
		{
			returnstate = 1;
			browsestate = leave;
		}	
	}
	if(is_changed==true)
	{
		sort (deleted_pics.begin(), deleted_pics.end());//sorts deleted pics
		for(int i=deleted_pics.size()-1;i>=0;--i)//starts from the end
		{
			namelist.erase(namelist.begin()+deleted_pics[i]);
		}
		ofstream indexout1;
		indexout1.open("index.txt",ios::trunc);//empties file
		for(int i=0;i<namelist_main.size(); ++i)//finds matches from old file to new
		{
			for(int j=0;j<namelist.size();++j)
			{
				if(namelist[j]->get_address()==namelist_main[i]->get_address())
				{
					namelist_main[i]->save(indexout1);
				}
			}
		}
	}
	hide();
}

bool browser_window::wait_for_button()//taken from simple window
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

void browser_window::cb_exit(Address, Address pw)
{
	reference_to<browser_window>(pw).exit();
}
void browser_window::exit()
{
	returnstate = 0;
	browsestate = leave;
	button_pushed = true;//for wait_for_button
}

void browser_window::cb_home(Address, Address pw)
{
	reference_to<browser_window>(pw).home();
}
void browser_window::home()
{
	browsestate = gohome;
	button_pushed = true;
}

void browser_window::cb_next(Address, Address pw)
{
	reference_to<browser_window>(pw).next();
}
void browser_window::next()
{
	detach(ii[index]);
	browsestate = rerun;
	if(index == ii.size()-1) 
		index = 0;
	else 
		++index;
	button_pushed= true;
}

void browser_window::cb_prev(Address, Address pw)
{
	reference_to<browser_window>(pw).prev();
}
void browser_window::prev()
{
	detach(ii[index]);
	browsestate = rerun;
	if(index == 0)
		index = ii.size()-1;
	else 
	--index;
	button_pushed= true;
}

void browser_window::cb_remove(Address, Address pw)
{
	reference_to<browser_window>(pw).remove();
}
void browser_window::remove()
{
	is_changed=true;
	detach(ii[index]);
	browsestate = leave;
	deleted_pics.push_back(index);
	returnstate =2;//runs it again
	button_pushed= true;
}
vector<string> browser_window::split(const string& s)//code borrowed from user AusCBloke on Stack Overflow
{
   vector<string> ret;
   typedef string::size_type string_size;
   string_size i = 0;

   // invariant: we have processed characters [original value of i, i) 
   while (i != s.size()) {
      // ignore leading blanks
      // invariant: characters in range [original i, current i) are all spaces
      while (i != s.size() && isspace(s[i]))
         ++i;

      // find end of next word
      string_size j = i;
      // invariant: none of the characters in range [original j, current j)is a space
      while (j != s.size() && !isspace(s[j]))
         j++;

      // if we found some nonwhitespace characters 
      if (i != j) {
         // copy from s starting at i and taking j - i chars
         ret.push_back(s.substr(i, j - i));
         i = j;
      }
   }
   return ret;
}
bool browser_window::is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}