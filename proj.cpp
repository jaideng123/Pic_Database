//Aggie snap project
//Main loop
//Esau Gallindo
//Forrest Hicks
//Jaiden Gerig
#include "std_lib_facilities_3.h"
#include "browser_window.h"
#include "home_window.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "picture.h"
int main()
{
	string search_string;
	int mainstate = 1;
	while (mainstate != 0)//main event loop
	{
		
		if (mainstate == 1)//home window
		{
			home_window win(Point(20,10),800,600,"Home window");
			mainstate = win.getstate();
			search_string = win.getsearch();//in case we're going to search
		}
		else if (mainstate == 2)//browser window
		{
			browser_window win(Point(20,10),800,600,"Browser window","ALLTAGS");
			mainstate = win.getstate();
		}
		else if (mainstate == 3)//search
		{
			browser_window win(Point(20,10),800,600,"Search window", search_string);//takes a search term
			mainstate = win.getstate();
		}
			
		else mainstate = 0;
	}
	return gui_main();
}

