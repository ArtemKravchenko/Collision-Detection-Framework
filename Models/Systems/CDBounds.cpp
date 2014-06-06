#include "CDBounds.h"


CDBounds::CDBounds(CDVector2D *blp, CDVector2D* tlp, CDVector2D *trp, CDVector2D *brp)
{
	BottomLeftPoint = blp;
	TopLeftPoint = tlp; 
	TopRightPoint = trp;
	BottomRightPoint = brp;
}

CDBounds::CDBounds()
{

}

CDBounds::~CDBounds(void)
{
	delete BottomLeftPoint;
	BottomLeftPoint = 0;
	delete TopLeftPoint;
	TopLeftPoint = 0;
	delete TopRightPoint;
	TopRightPoint = 0;
	delete BottomRightPoint;
	BottomRightPoint = 0;
}
