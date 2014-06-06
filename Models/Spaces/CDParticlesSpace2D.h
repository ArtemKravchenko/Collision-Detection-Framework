#pragma once
#include "CDParticlesCollisionDetection2DLogic.h"
#include "CDParticlesPhysicLogic.h"

class CDParticlesSpace2D
{
private:
	CDParticlesList *_particles;	 
	CDParticlesCollisionDetection2DLogic *_collisionDetectionLogic;
	CDParticlesPhysicLogic *_physicLogic;
	int _width;
	int _height;

public:
	CDParticlesSpace2D(CDParticlesList *particles, int width, int height);
	~CDParticlesSpace2D(void);

	void MoveParticlesInSpaceInTime(int time);
};

