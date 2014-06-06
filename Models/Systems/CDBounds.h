#pragma once
#include "CDVector2D.h"

class CDBounds
{
public:
	CDVector2D *BottomLeftPoint;
	CDVector2D *TopLeftPoint;
	CDVector2D *TopRightPoint;
	CDVector2D *BottomRightPoint;

	CDBounds(CDVector2D *blp, CDVector2D* tlp, CDVector2D *trp, CDVector2D *brp);
	CDBounds();
	~CDBounds(void);
};

