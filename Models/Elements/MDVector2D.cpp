
#include "MDVector2D.h"


MDVector2D::MDVector2D(int x, int y)
{
	this->X = x;
	this->Y = y;
}


MDVector2D::~MDVector2D(void)
{
	X = 0;
	Y = 0;
}
