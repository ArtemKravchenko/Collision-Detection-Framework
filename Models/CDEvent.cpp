#include "CDEvent.h"


CDEvent::CDEvent(CDEventType eventType, float timeToEvent, CDParticle2D* p1, CDParticle2D* p2, int xBound, int yBound)
{
    EventType = eventType;
    TimeToEvent = timeToEvent;
    Particle1 = p1;
    Particle2 = p2;
    XBound = xBound;
    YBound = yBound;
}


CDEvent::~CDEvent(void)
{
}
