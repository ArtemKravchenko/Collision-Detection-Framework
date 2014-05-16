#pragma once
#include "MDParticlesSystem.h"
#include <unordered_map>
#include "MDCollisionPair.h"

static int _countOfNeighborhood = 4; 
typedef std::unordered_map<int, std::vector<int>>	MDNeighborhoodMap;
typedef std::pair<int, std::vector<int>>			MDNeighborhoodPair;
typedef std::vector<MDParticlesSystem*>				MDSubsystemsList;
typedef	std::vector<MDCollisionPair*>				MDCollisionPairsList;

class MDParticlesCollisionDetection2DLogic
{
private:
	int						_countOfRows;
	int						_countOfColumns; 
	int						_subsystemWidth;
	int						_subsystemHeight;
	int						_actualCountOfSubsystems; 
	float					_minTime;
	int						_width;						// Width of space
	int						_height;					// Height of space
	float					_eps;						// Error of computations
	MDNeighborhoodMap		*_neighborhood;
	MDCollisionPairsList	*_collisionPairs;			// Pairs of objects that going to collect in _minTime

	MDSubsystemsList	*_subsystems;

	void InitSubsystems(MDParticlesList *particles);
	
	float DetectCollisionBetweenTwoParticles(MDParticle2D *p1, MDParticle2D *p2);
	float DetectCollisionBetweenParticleAndBound(MDParticle2D *p, int boundOrigin, bool isVerticalBound);
	void AddCollisionPairToList(MDParticle2D *p1, MDParticle2D *p2, float xBound, float yBound, bool clearCollisionPairList);
	void TryAddCollsionPairToList(MDParticle2D *p1, MDParticle2D *p2, float xBound, float yBound);
	void ComputeMinimalTimeOfCollision(int time);
	void ChangeVelocityAfterTwoParticleCollision(MDParticle2D *p1, MDParticle2D *p2);
	void ChangeVelocityAfterParticlesCollisionWithBound(MDParticle2D *p, float bound);

public:
	MDParticlesCollisionDetection2DLogic(MDParticlesList *particles, int width, int height, int countOfRows, int countOfCols);
	~MDParticlesCollisionDetection2DLogic(void);
	
    void DecectCollisionBetweenParticlesInTime(int time);
};
/*
 ------------------------------------------ DESCRIPTION ------------------------------------------
 
 Current class implement base particles collision detection logic.
 For using current class client need:
 1.) Size of space where you going to work
 2.) List of particles, which you will obsere in experiments
 3.) Count of columns and count of rows which devide space where experiments happen on subsystems
 
 What class already have:
 
 
 ------------------------------------------ ALGORITHM ------------------------------------------
 
 0.) Split spcae into subsystems. Provide each particle his own subsystem.
 1.) Order the heap with times of collision in particles motion.
    1.1) - Loop through each subsystems,
         - detect time when each particles into current subsystem:
            - collides with other particles into current subsystem
            - collides with particles into neighbors subsystems
            - left current subsystem
            - collide with the bound of space (if current subsystem is boundary)
 2.) Consider inequality (currentTime - "local Time Of particle that will be take part in nearest event (nextEventParticle)"
                                      + "difference in time between local time of nextEventParticle and time of nearestEvent")
                          < error - defined error
 3.) If inequality is satisfied:
    3.1) If next event describes collision between particles, then change velocity of particles.
    3.2) If next event describes collision between particle and bounds, then change velocity of particle.
    3.3) After both previous cases we should remove all events in which our collided particles take parts and
        and go to step 1.
    3.4) If next event describes that particles going to left current subsystem, then change subsystem of current particle.
 
 4.) If inequality is not satisfied - do nothing.
*/