
#include "MDParticlesSystem.h"



MDParticlesSystem::MDParticlesSystem(MDVector2D *blp, MDVector2D *tlp, MDVector2D *trp, MDVector2D *brp) : MDAbstractSystem(blp, tlp, trp, brp)
{

}

MDParticlesSystem::MDParticlesSystem() : MDAbstractSystem()
{
	// TODO: n
}

MDParticlesSystem::~MDParticlesSystem(void)
{
	// Clear list of paticles
	Particles->clear();
	delete Particles;
	Particles = 0;
}

void MDParticlesSystem::AddParticle(MDParticle2D *particle)
{
	Particles->push_back(particle);
}