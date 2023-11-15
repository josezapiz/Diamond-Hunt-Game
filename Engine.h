#ifndef Engine_h
#define Engine_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <ncurses.h>
#include "Movement.h"
#include "Potter.h"
#include "Malfoy.h"

using namespace std;

class Potter;
class Malfoy;

class Engine
{
private:
    fstream file;
    string line;

	vector<string> map;
	vector<int> diamond_pos;
	
	Potter* pot;
	Malfoy* mal;

public:

	Engine(int, char **a); //constructor

	void save_map(int, char**);
	void load_map();

	void valid_XY(vector<int>&, vector<int>&);

	void diamond_position();

	int collision(); //check collision between Potter and Diamond

	vector<string> get_map() const;
	vector<int> get_diamond_pos() const;
	void start(); //start engine

};
#endif