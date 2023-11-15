#include "Movement.h"
#include "Engine.h"
using namespace std;

Movement::Movement(Engine* e, int y, int x)
{
	this->e = e;
	this->y = y;
	this->x = x;
}

int Movement::get_y() const
{
	return y;
}
int Movement::get_x() const
{
	return x;
}

void Movement::set_y(const int y)
{
	this->y = y;
}
void Movement::set_x(const int x)
{
	this->x = x;
}