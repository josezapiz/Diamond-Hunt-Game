#ifndef Malfoy_h
#define Malfoy_h
#include "Movement.h"
#include <ncurses.h>
#include <vector>
using namespace std;

class Malfoy: public Movement
{
private:
	char symbol;
public:
	Malfoy(Engine*, int, int, char);

	int getMove();
	bool visited(const vector<pair<int,int>>&, const int&, const int&);

	void show();
};
#endif