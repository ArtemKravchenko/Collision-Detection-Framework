#include "MDBounds.h"


MDBounds::MDBounds(MDVector2D *blp, MDVector2D* tlp, MDVector2D *trp, MDVector2D *brp)
{
	BottomLeftPoint = blp;
	TopLeftPoint = tlp; 
	TopRightPoint = trp;
	BottomRightPoint = brp;
}

MDBounds::MDBounds()
{

}

MDBounds::~MDBounds(void)
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
