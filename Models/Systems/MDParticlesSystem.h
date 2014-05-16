#pragma once
#include "MDAbstractSystem.h"
#include "MDParticle2D.h"
#include <vector>

typedef std::vector<MDParticle2D*> MDParticlesList; 


class MDParticlesSystem :
	public MDAbstractSystem
{
public:
	MDParticlesList *Particles;

	MDParticlesSystem(MDVector2D *blp, MDVector2D *tlp, MDVector2D *trp, MDVector2D *brp);
	MDParticlesSystem();
	~MDParticlesSystem(void);
	
	void AddParticle(MDParticle2D *particle);
};

