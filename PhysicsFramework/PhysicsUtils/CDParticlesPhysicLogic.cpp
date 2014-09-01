
#include "CDParticlesPhysicLogic.h"

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
CDParticlesPhysicLogic::CDParticlesPhysicLogic(CDParticlesList *particles)
{
	_particles = particles;
}

CDParticlesPhysicLogic::~CDParticlesPhysicLogic(void)
{
	_particles->clear();
	delete _particles;
	_particles = 0;
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
void CDParticlesPhysicLogic::MoveParticlesInSpace2DInTime(int time)
{
	// TODO: need to implement
}
