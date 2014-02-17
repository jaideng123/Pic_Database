//error_window.h
//Jaiden Gerig
//a basic window to tell the user when something's gone wrong
#ifndef ERROR_WINDOW_H
#define ERROR_WINDOW_H

#include "GUI.h"  
#include "Graph.h"
#include "Window.h"
using namespace Graph_lib;

struct error_window : Graph_lib::Window
{
	error_window(Point xy, int w, int h, const string& title,string error_msg);
	bool wait_for_button();
private:
	bool button_pushed;
	
	Out_box error_box;
	
	Button exit_button;
	
	static void cb_exit(Address, Address);
	void exit();
	
};

#endif