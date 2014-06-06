
#include "CDVector2D.h"


CDVector2D::CDVector2D(int x, int y)
{
	this->X = x;
	this->Y = y;
}


CDVector2D::~CDVector2D(void)
{
	X = 0;
	Y = 0;
}
