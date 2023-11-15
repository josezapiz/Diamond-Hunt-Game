#include <iostream>
#include <ncurses.h>
#include "Engine.h"

using namespace std;


int main (int argc, char **argv)
{
	try
	{
		//Construct Game Engine
		Engine e(argc,argv);
		//Start Game
		e.start();
	}
	catch(int e)
	{
		cout << "ERROR. Problem with file" << endl;
	}

	
	
	return 0;
}