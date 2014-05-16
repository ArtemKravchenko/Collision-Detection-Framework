#pragma once
#include "MDVector2D.h"

class MDParticle2D
{
public:
	MDVector2D	*Position;
	MDVector2D	*Velocity;
	int			LocalTime;

	MDParticle2D(MDVector2D	*position, MDVector2D	*velocity);
	~MDParticle2D(void);
};

