#pragma once
#include "CDParticlesSystem.h"
#include <unordered_map>
#include "CDEvent.h"
#include "DSHeap.h"

static int _countOfNeighborhood = 4; 
// The Key - is the index of current subsystem. The Value - is the list of index owned susystmes
typedef std::unordered_map<int, std::vector<int>>							CDNeighborhoodMap;
typedef std::pair<int, std::vector<int>>									CDNeighborhoodPair;
typedef std::vector<CDParticlesSystem*>										CDSubsystemsList;
typedef std::vector<CDEvent*>												CDEventsList;

class CDParticlesCollisionDetection2DLogic
{
private:
	//--------------------------------- Variables ----------------------------------------------//
	int						_countOfRows;
	int						_countOfColumns; 
	int						_actualCountOfSubsystems;
	int						_width;						// Width of space
	int						_height;					// Height of space
	int						_subsystemWidth;
	int						_subsystemHeight;
	float					_eps;						// Error of computations
	
	CDSubsystemsList		*_subsystems;
	CDNeighborhoodMap		*_neighborhoodOwned;
	CDNeighborhoodMap		*_neighborhoodOwning;
	CDEventsList			*_eventsList;
    DSHeap<CDEvent*>        *_heap;
	
	
	//--------------------------------- Functions ----------------------------------------------//
	void InitSubsystems(CDParticlesList *particles);
	void InitNeighbors(bool isOwnedNeighbors, int subsystemIndex);
    void InitListOfEvents();
    void inline DetectCollisionBetweenParticleAndParticlesInSystem(CDParticle2D *particle, CDParticlesSystem *system, bool needToAdd);
    void inline DetectCollisionBetwennParticleAndBoundsOfSystem(CDParticle2D *particle, CDParticlesSystem *system, bool needToAdd);
	float DetectCollisionBetweenTwoParticles(CDParticle2D *p1, CDParticle2D *p2);
	float DetectCollisionBetweenParticleAndBound(CDParticle2D *p, int boundOrigin, bool isVerticalBound);
    float DetectWhenParticleLeftSubsystem(CDParticle2D *p, CDParticlesSystem *subsystem);
	void ComputeMinimalTimeOfCollision(int time);
	void ChangeVelocityAfterTwoParticleCollision(CDParticle2D *p1, CDParticle2D *p2);
	void ChangeVelocityAfterParticlesCollisionWithBound(CDParticle2D *p, float bound);
	void FillEventsListWithTime(int time); 

public:
	CDParticlesCollisionDetection2DLogic(CDParticlesList *particles, int width, int height, int countOfRows, int countOfCols);
	~CDParticlesCollisionDetection2DLogic(void);
	
	void DecectCollisionBetweenParticlesInTime(int time);
};


/*

---------------------------------------------------------------------- Algorithm ----------------------------------------------------------------------

0.) Initialize all data structures that take part in computation. (initialze vector of subsystems, neighbors)
	0.1) Initialize all local fields that passing through constructor.
	0.2) Initialize all subsystems put into subsystem their own particles.
	0.3) Initialize all neighbors of each subsystem.
1.) Loop through all subsystmes and determine minimal time of collision (Func1)
	1.1) For each particle in current subsytem determine time (after each determination - add to vector of events):
		 - of collision with each particles in current subsystem											(Func2) (EventType1) 
		 - of collision with each particles in neighbors subsystems (only owned neighbors)					(Func3) (EventType1)
		 - when particle left current subsystem																(Func4) (EventType2)
		 - of collision with boundaries of space (need to determine only when our subsystem is boundary)	(Func5) (EventType3)
	1.2) Insert each event in priority queue
2.) Wait throughout discrete time when next event happens.
3.) Make the changes
	3.1) If type of event that happens is EventType1 or EventType3  ->
	- change velocity of particles that take part in collision										(Func6)
	- need to recompute time in those events that contain at least one particles from collided ones	(Func7)
	- need to change time in remaining events (need to substract from localEventTime to collision difference in time that has passed)
	3.2) If type of event that happens is EventType2 ->
	- remove all events in which considered particle will be take part
	- execute (Func1) (for all neighbors)
	- remove particle from previous subsystem
	- add particle to new susbsystem

---------------------------------------------------------------------- Implementation -----------------------------------------------------------------



*/

