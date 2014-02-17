//error_window.cpp
//Jaiden Gerig
//a basic window to tell the user when something's gone wrong
#include "error_window.h"
#include <string>
#include "std_lib_facilities_3.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;
error_window::error_window(Point xy, int w, int h, const string& title,string error_msg)
	:Window(xy,w,h,title),
	exit_button(Point((x_max())/2,y_max()-20),70,20,"OK",cb_exit),
	error_box(Point((x_max()/2)-30,y_max()/2),150,30,"ERROR:")
	{
	attach(exit_button);
	attach(error_box);
	error_box.put(error_msg);
	wait_for_button();
	hide();
	}

bool error_window::wait_for_button()//taken from simple window
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
void error_window::cb_exit(Address, Address pw)
{
	reference_to<error_window>(pw).exit();
}
void error_window::exit()
{
	button_pushed = true;//for wait_for_button
}