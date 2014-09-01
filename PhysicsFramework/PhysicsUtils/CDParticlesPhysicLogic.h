#pragma once
#include "CDParticlesSystem.h"

class CDParticlesPhysicLogic
{
public:

	CDParticlesPhysicLogic(CDParticlesList *particles);
	~CDParticlesPhysicLogic(void);

	void MoveParticlesInSpace2DInTime(int time);
private:
    CDParticlesList		*_particles;
};

