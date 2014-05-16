#pragma once
#include "MDBounds.h"

class MDAbstractSystem
{
public:
	MDBounds *Bounds;  
	MDAbstractSystem(MDVector2D *blp, MDVector2D *tlp, MDVector2D *trp, MDVector2D *brp);
	MDAbstractSystem();
	~MDAbstractSystem(void);
};

