#ifndef Moving_h
#define Moving_h
#include <iostream>
#include <vector>

class Engine;

class Movement
{
protected: //access only to inherited classes
    Engine* e;
    int y; //coordinate y
	int x; //coordinate x
public:
	Movement(Engine*, int, int);
    virtual ~Movement(){};
    
    virtual int getMove () = 0; //move method, 
    //the inherited class will have its own move algorith.
    //~~ (Keyboard for Potter (Player)) and "Smart" algorithm for Malfoy ~~~

    int get_y() const;
    int get_x() const;
    
    void set_y(const int);
    void set_x(const int);
};
#endif