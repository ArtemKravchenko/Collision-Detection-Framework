#include "MDParticle2D.h"


MDParticle2D::MDParticle2D(MDVector2D	*position, MDVector2D	*velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}


MDParticle2D::~MDParticle2D(void)
{
	delete Position;
	Position = 0;
	delete Velocity;
	Velocity = 0;
}
