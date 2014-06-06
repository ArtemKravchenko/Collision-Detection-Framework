#pragma once

#include "CDParticle2D.h"

enum CDEventType {
	CollisionBetweenTwoParticles = 1,
	CollisionBetweenParticleAndBoundary,
	ParticleGointToLeaveSystem
};

class CDEvent
{
public:
	CDEventType			EventType;
	float				TimeToEvent;

	CDParticle2D		*Particle1;
	CDParticle2D		*Particle2;
	int					XBound;
	int					YBound;

	CDEvent(CDEventType eventType, float timeToEvent, CDParticle2D* p1, CDParticle2D* p2, int xBound, int yBound);
	~CDEvent(void);
    
    static int compareFunction(CDEvent* event1, CDEvent* event2)
	{
        if (event1->TimeToEvent > event2->TimeToEvent)
            return 1;
        else if (event1->TimeToEvent < event2->TimeToEvent)
            return -1;
		return 0;
	}
};



