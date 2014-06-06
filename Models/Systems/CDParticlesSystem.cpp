
#include "CDParticlesSystem.h"



CDParticlesSystem::CDParticlesSystem(CDVector2D *blp, CDVector2D *tlp, CDVector2D *trp, CDVector2D *brp) : CDAbstractSystem(blp, tlp, trp, brp)
{

}

CDParticlesSystem::CDParticlesSystem() : CDAbstractSystem()
{
	// TODO: n
}

CDParticlesSystem::~CDParticlesSystem(void)
{
	// Clear list of paticles
	Particles->clear();
	delete Particles;
	Particles = 0;
}

void CDParticlesSystem::AddParticle(CDParticle2D *particle)
{
	Particles->push_back(particle);
}