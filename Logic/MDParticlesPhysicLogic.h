#pragma once
#include "MDParticlesSystem.h"

class MDParticlesPhysicLogic
{
public:
	MDParticlesList		*_particles;

	MDParticlesPhysicLogic(MDParticlesList *particles);
	~MDParticlesPhysicLogic(void);

	void MoveParticlesInSpace2DInTime(int time);
};

