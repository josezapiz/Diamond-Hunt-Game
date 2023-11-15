#include "Potter.h"
#include "Engine.h"

using namespace std;

Potter::Potter(Engine* e, int y, int x, char s) : Movement(e,y,x)
{
    symbol = s;
}

int Potter::getMove()
{	
    int c;
    do
    {
        c = getch(); //get keyboard key

        if((c == KEY_UP) && (e->get_map()[y-1][x] != '*'))
        {
            //if the position is not wall
            return 1;
        }
        else if((c == KEY_DOWN) && (e->get_map()[y+1][x] != '*'))
        {
            return 2;
        }
        else if((c == KEY_LEFT) && (e->get_map()[y][x-1] != '*'))
        {
            return 3;	
        }
        else if((c == KEY_RIGHT) && (e->get_map()[y][x+1] != '*'))
        {
            return 4;
        }
        else if(c == 32) // 32 → space
        {
            return 5; //if space, καμία αλλαγή στα y και x
        }
        else if(c == 27) //27 → esc
        {
            return 6;
        }	 	

    } while (c != -1);
  
    return -1;
}

void Potter::show()
{
    attron(COLOR_PAIR(1));
	mvaddch(this->y,this->x,symbol);
    attroff(COLOR_PAIR(1));
}