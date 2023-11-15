#ifndef Potter_h
#define Potter_h
#include "Movement.h"
#include <ncurses.h>

class Potter: public Movement
{
private:
	char symbol;
public:
	Potter(Engine* , int, int, char);

	int getMove(); //move algorithm
	void show(); //draw on screen

};
#endif