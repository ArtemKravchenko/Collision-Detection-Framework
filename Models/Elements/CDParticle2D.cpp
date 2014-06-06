#include "CDParticle2D.h"


CDParticle2D::CDParticle2D(CDVector2D	*position, CDVector2D	*velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}


CDParticle2D::~CDParticle2D(void)
{
	delete Position;
	Position = 0;
	delete Velocity;
	Velocity = 0;
}
