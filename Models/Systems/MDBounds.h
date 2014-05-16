#pragma once
#include "MDVector2D.h"

class MDBounds
{
public:
	MDVector2D *BottomLeftPoint;
	MDVector2D *TopLeftPoint;
	MDVector2D *TopRightPoint;
	MDVector2D *BottomRightPoint;

	MDBounds(MDVector2D *blp, MDVector2D* tlp, MDVector2D *trp, MDVector2D *brp);
	MDBounds();
	~MDBounds(void);
};

