#pragma once
#include "CDParticlesSystem.h"

class CDParticlesPhysicLogic
{
public:
	CDParticlesList		*_particles;

	CDParticlesPhysicLogic(CDParticlesList *particles);
	~CDParticlesPhysicLogic(void);

	void MoveParticlesInSpace2DInTime(int time);
};

