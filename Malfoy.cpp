#include "Malfoy.h"
#include "Engine.h"
using namespace std;

Malfoy::Malfoy(Engine* e, int y, int x, char s) : Movement(e,y,x)
{
    symbol = s;
}

int Malfoy::getMove()
{
    /*  
    Starting search from diamond coordinates
    Back-tracking to find the shortest route possible that Malfoy can take
    */
    int current_y = e->get_diamond_pos()[0];
    int current_x = e->get_diamond_pos()[1];

    vector<pair<int,int>> path; //pushing the coordinates to a vector

    path.push_back(make_pair(current_y,current_x));

    for(int i=0; i<path.size(); i++) //check every possible path
    {   

        //if up-space is available AND not visited
        if((e->get_map()[path[i].first-1][path[i].second]) != '*' && (!visited(path, path[i].first-1, path[i].second)))
        {
            if((path[i].first-1 == this->y) && (path[i].second == this->x)) //if Malfoy is up
            {
                return 1;
            }
            else
            {
                path.push_back(make_pair(path[i].first-1, path[i].second));//if up-space is available, push it in the path
            }

        }
        //if down-space is avaiable AND not visited
        if((e->get_map()[path[i].first+1][path[i].second]) != '*' && (!visited(path, path[i].first+1, path[i].second)))
        {
            if((path[i].first+1 == this->y) && (path[i].second == this->x))//if Malfoy in down-space
            {
                return 2;
            }
            else
            {
                path.push_back(make_pair(path[i].first+1, path[i].second));//if down-space is available, push it in the path
            }

        }
        //if left-space available AND not visited
        if((e->get_map()[path[i].first][path[i].second-1]) != '*' && (!visited(path, path[i].first, path[i].second-1)))
        {
            if((path[i].first == this->y) && (path[i].second-1 == this->x))//if Malfoy on left-space
            {
                return 3;
            }
            else
            {
                path.push_back(make_pair(path[i].first, path[i].second-1));//if left-space is available, push it in the path
            }

        }
        //if right-space available AND not visited
        if((e->get_map()[path[i].first][path[i].second+1]) != '*' && (!visited(path, path[i].first, path[i].second+1)))
        {
            if((path[i].first == this->y) && (path[i].second+1 == this->x))//if Malfoy on right-space
            {
                return 4;
            }
            else
            {
                path.push_back(make_pair(path[i].first, path[i].second+1));//if right-space is available, push it in the path
            }

        }
    }
    return -1;
}

//check if a position is visited
bool Malfoy::visited(const vector<pair<int,int>>& p, const int& tmpy, const int& tmpx)
{
    for(int i=0; i<p.size(); i++)
    {
        if(p[i].first == tmpy && p[i].second == tmpx)
        {
            return true;
        }
    }
    return false;
}

void Malfoy::show()
{
    attron(COLOR_PAIR(2));
	mvaddch(this->y,this->x,symbol);
    attroff(COLOR_PAIR(2));
}