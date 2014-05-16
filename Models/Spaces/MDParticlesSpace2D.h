#pragma once
#include "MDParticlesCollisionDetection2DLogic.h"
#include "MDParticlesPhysicLogic.h"

class MDParticlesSpace2D
{
private:
	MDParticlesList *_particles;	 
	MDParticlesCollisionDetection2DLogic *_collisionDetectionLogic;
	MDParticlesPhysicLogic *_physicLogic;
	int _width;
	int _height;

public:
	MDParticlesSpace2D(MDParticlesList *particles, int width, int height);
	~MDParticlesSpace2D(void);

	void MoveParticlesInSpaceInTime(int time);
};

