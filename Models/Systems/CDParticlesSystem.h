#pragma once
#include "CDAbstractSystem.h"
#include "CDParticle2D.h"
#include <vector>

typedef std::vector<CDParticle2D*> CDParticlesList; 


class CDParticlesSystem :
	public CDAbstractSystem
{
public:
	CDParticlesList *Particles;

	CDParticlesSystem(CDVector2D *blp, CDVector2D *tlp, CDVector2D *trp, CDVector2D *brp);
	CDParticlesSystem();
	~CDParticlesSystem(void);
	
	void AddParticle(CDParticle2D *particle);
};

