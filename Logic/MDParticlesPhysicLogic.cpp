
#include "MDParticlesPhysicLogic.h"

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
MDParticlesPhysicLogic::MDParticlesPhysicLogic(MDParticlesList *particles)
{
	_particles = particles;
}

MDParticlesPhysicLogic::~MDParticlesPhysicLogic(void)
{
	_particles->clear();
	delete _particles;
	_particles = 0;
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
void MDParticlesPhysicLogic::MoveParticlesInSpace2DInTime(int time)
{
	// TODO: need to implement
}
