#pragma once
#include "CDVector2D.h"

class CDParticle2D
{
public:
	CDVector2D	*Position;
	CDVector2D	*Velocity;
	int			LocalTime;

	CDParticle2D(CDVector2D	*position, CDVector2D	*velocity);
	~CDParticle2D(void);
};

