#pragma once
#include "CDBounds.h"

class CDAbstractSystem
{
public:
	CDBounds *Bounds;  
	CDAbstractSystem(CDVector2D *blp, CDVector2D *tlp, CDVector2D *trp, CDVector2D *brp);
	CDAbstractSystem();
	~CDAbstractSystem(void);
};

