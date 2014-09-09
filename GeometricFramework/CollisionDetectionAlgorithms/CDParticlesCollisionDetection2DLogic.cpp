#include "CDParticlesCollisionDetection2DLogic.h"
#include <cmath>

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
CDParticlesCollisionDetection2DLogic::CDParticlesCollisionDetection2DLogic(CDParticlesList *particles, int width, int height, int countOfRows, int countOfCols)
{
	_countOfRows = countOfRows;
	_countOfColumns = countOfCols;
	_actualCountOfSubsystems = countOfRows * countOfCols; _countOfRows = countOfRows;
	_width = width;
	_height = height;
	_subsystemWidth = width / countOfCols; 
	_subsystemHeight = height / countOfRows;
	_eps = 0.000001;					
	
	_subsystems = new CDSubsystemsList(_actualCountOfSubsystems); 
	_neighborhoodOwned = new CDNeighborhoodMap();
	_neighborhoodOwning = new CDNeighborhoodMap();
	this->InitSubsystems(particles);
	_eventsList = new CDEventsList();
    this->InitListOfEvents();
    _heap = new DSHeap<CDEvent*>(_eventsList, &CDEvent::compareFunction);
}

CDParticlesCollisionDetection2DLogic::~CDParticlesCollisionDetection2DLogic(void)
{
	_subsystems->clear();
	delete _subsystems;
	_subsystems = 0;
	
	_neighborhoodOwned->clear();
	delete _neighborhoodOwned;
	_neighborhoodOwned = 0;

	_neighborhoodOwning->clear();
	delete _neighborhoodOwning;
	_neighborhoodOwning = 0;

	_eventsList->clear();
	delete _eventsList;
	_eventsList = 0;
    
    delete _heap;
    _heap = 0;
}
//--------------------------------------------------------------------
// Private functions
//--------------------------------------------------------------------
void CDParticlesCollisionDetection2DLogic::InitSubsystems(CDParticlesList *particles)
{
	int multiindexOfSystem;
	unsigned long countOfParticles = particles->size();
	// Init subsystems
	for(int i = 0; i < countOfParticles; i++)
	{
		CDParticle2D *particle = particles->at(i);
        multiindexOfSystem = 0; // TODO: Unexpected remove CDUtils::GetMultiIndexOfSubsystem(static_cast<int>(particle->Position->X), static_cast<int>(particle->Position->Y), _subsystemWidth, _subsystemHeight, _countOfColumns);
		CDParticlesSystem *particleSystem = this->_subsystems->at(multiindexOfSystem);
		if(particleSystem == NULL)
		{
			particleSystem = new CDParticlesSystem();
		}
		particleSystem->AddParticle(particle);
	}
    
	
	for(int i = 0; i < _actualCountOfSubsystems; i++)
	{
		CDParticlesSystem *particlesSystem = this->_subsystems->at(i);
		if(particlesSystem == NULL)
		{
			particlesSystem = new CDParticlesSystem();
			// Init system bounds
			particlesSystem->Bounds = new CDBounds();
			particlesSystem->Bounds->BottomLeftPoint = new CDVector2D(static_cast<float>(_subsystemWidth * i), static_cast<float>(_subsystemHeight * i));
			particlesSystem->Bounds->TopLeftPoint = new CDVector2D(static_cast<float>(_subsystemWidth * i), static_cast<float>(_subsystemHeight * i + _subsystemHeight));
			particlesSystem->Bounds->TopRightPoint = new CDVector2D(static_cast<float>(_subsystemWidth * i + _subsystemWidth), static_cast<float>(_subsystemHeight * i + _subsystemHeight));
			particlesSystem->Bounds->BottomRightPoint = new CDVector2D(static_cast<float>(_subsystemWidth * i + _subsystemWidth), static_cast<float>(_subsystemHeight * i));
		}
		// Init owned neighborhood
		this->InitNeighbors(true, i);
		// Init owning neighbors
		this->InitNeighbors(false, i);
	}
}

void CDParticlesCollisionDetection2DLogic::InitNeighbors(bool isOwnedNeighbors, int subsystemIndex)
{
	int firstNeighbor, secondNeighbor, thirdNeighbor, fourthNeighbor;
	bool condition;
	std::vector<int> currentNeighborhood;//= new std::vector<int>();
	for(int j = 0; j < _countOfNeighborhood; j++)
	{
		// Init number of first neighbor
		firstNeighbor = (subsystemIndex + (isOwnedNeighbors)) ?  - (_countOfColumns - 1) : (_countOfColumns - 1);
		condition = (isOwnedNeighbors) ? (firstNeighbor > 0 && firstNeighbor % _countOfColumns != 0) : (firstNeighbor < _actualCountOfSubsystems && (firstNeighbor + 1) % _countOfColumns != 0);
		if(condition) // if number of first neighbor isn't higer than upper bound and not more right than right bound
			currentNeighborhood.push_back(firstNeighbor);
		// Init number of second neighbor
		secondNeighbor = (subsystemIndex + (isOwnedNeighbors)) ?  1 : - 1;
		condition = (isOwnedNeighbors) ? (secondNeighbor % _countOfColumns != 0) : ((firstNeighbor + 1) % _countOfColumns != 0);
		if(condition) // if number of second neighbor isn't more right than right bound
			currentNeighborhood.push_back(secondNeighbor);
		// Init number of third neighbor
		thirdNeighbor = (subsystemIndex + (isOwnedNeighbors)) ?  _countOfColumns : - _countOfColumns;
		condition = (isOwnedNeighbors) ? (thirdNeighbor < _actualCountOfSubsystems) : (thirdNeighbor > 0);
		if(condition)
		{
			currentNeighborhood.push_back(thirdNeighbor);
			// Init fourth neighbor
			fourthNeighbor = (isOwnedNeighbors) ? thirdNeighbor + 1 : thirdNeighbor - 1;
			condition = (isOwnedNeighbors) ? (fourthNeighbor % _countOfColumns != 0) : ((fourthNeighbor + 1) % _countOfColumns != 0);
			if(condition)
				currentNeighborhood.push_back(fourthNeighbor);
		}
		CDNeighborhoodPair p = CDNeighborhoodPair(subsystemIndex, currentNeighborhood);
		if(isOwnedNeighbors)
			_neighborhoodOwned->insert(p);
		else
			_neighborhoodOwning->insert(p);
	}
}

void CDParticlesCollisionDetection2DLogic::InitListOfEvents()
{
	unsigned long subsystemListSize = this->_subsystems->size();
	unsigned long particlesListSize = -1;
    std::vector<int> *currentNeighborhood;
    int subsystemIndex;
    
    
	CDParticlesSystem *tmpSystem;
    CDParticlesSystem *tmpNeighborSystem;
	CDParticle2D *tmpParticle;
	// 1.) Loop through all subsystmes and determine minimal time of collision
	for(unsigned int i = 0; i < subsystemListSize; i++)
	{
		tmpSystem = this->_subsystems->at(i);
		// Loop through all particles in subsystem
		particlesListSize = tmpSystem->Particles->size();
		// 1.1) For each particle in current subsytem determine time :
		for(unsigned int j = 0; j < particlesListSize; j++)
		{
			tmpParticle = tmpSystem->Particles->at(j);
			// - of collision with each particles in current subsystem
			this->DetectCollisionBetweenParticleAndParticlesInSystem(tmpParticle, tmpSystem, true);
            // - of collision with each particles in neighbors subsystems (only owned neighbors)
            currentNeighborhood = &_neighborhoodOwned->find(i)->second;
            for (unsigned int j2 = 0; j2 < currentNeighborhood->size(); j2++)
            {
                subsystemIndex = currentNeighborhood->at(i);
                tmpNeighborSystem = _subsystems->at(subsystemIndex);
                this->DetectCollisionBetweenParticleAndParticlesInSystem(tmpParticle, tmpNeighborSystem, true);
            }
            // - when particle left current subsystem
            this->DetectWhenParticleLeftSubsystem(tmpParticle, tmpSystem);
            // of collision with boundaries of space (need to determine only when our subsystem is boundary)
            this->DetectCollisionBetwennParticleAndBoundsOfSystem(tmpParticle, tmpSystem, true);
		}
	}
}

float CDParticlesCollisionDetection2DLogic::DetectCollisionBetweenTwoParticles(CDParticle2D *p1, CDParticle2D *p2)
{
	return 0; // TODO: need to implement
}

float CDParticlesCollisionDetection2DLogic::DetectCollisionBetweenParticleAndBound(CDParticle2D *p, int boundOrigin, bool isVerticalBound)
{
	return 0; // TODO: need to implement
}


float CDParticlesCollisionDetection2DLogic::DetectWhenParticleLeftSubsystem(CDParticle2D *p, CDParticlesSystem *subsystem)
{
    return 0;
}

void inline CDParticlesCollisionDetection2DLogic::DetectCollisionBetweenParticleAndParticlesInSystem(CDParticle2D* particle, CDParticlesSystem *system, bool needToAdd)
{
    unsigned long particlesListSize = system->Particles->size();
    CDParticle2D *tmpSecondParticle;
    float tmpTime;
    
    for(unsigned int i = 0; i < particlesListSize; i++)
    {
        tmpSecondParticle = system->Particles->at(i);
        if (particle != tmpSecondParticle)
        {
            tmpTime = this->DetectCollisionBetweenTwoParticles(particle, tmpSecondParticle);
            if (needToAdd)
            {
                CDEvent *event = new CDEvent(CollisionBetweenTwoParticles, tmpTime, particle, tmpSecondParticle, -1, -1);
                _eventsList->push_back(event);
            }
        }
    }
}

void inline CDParticlesCollisionDetection2DLogic::DetectCollisionBetwennParticleAndBoundsOfSystem(CDParticle2D *particle, CDParticlesSystem *system, bool needToAdd)
{
    float tmpTime;
    if (system->Bounds->BottomLeftPoint->X == 0)
    {
        tmpTime = this->DetectCollisionBetweenParticleAndBound(particle, system->Bounds->BottomLeftPoint->X, false);
        if (needToAdd)
        {
            CDEvent *event = new CDEvent(ParticleGointToLeaveSystem, tmpTime, particle, NULL, system->Bounds->BottomLeftPoint->X, -1);
            _eventsList->push_back(event);
        }
    }
    if (system->Bounds->BottomLeftPoint->Y == 0)
    {
        tmpTime = this->DetectCollisionBetweenParticleAndBound(particle, system->Bounds->BottomLeftPoint->Y, true);
        if (needToAdd)
        {
            CDEvent *event = new CDEvent(ParticleGointToLeaveSystem, tmpTime, particle, NULL, -1, system->Bounds->BottomLeftPoint->Y);
            _eventsList->push_back(event);
        }
    }
    if (system->Bounds->TopRightPoint->X == _width)
    {
        tmpTime = this->DetectCollisionBetweenParticleAndBound(particle, system->Bounds->TopRightPoint->X, false);
        if (needToAdd)
        {
            CDEvent *event = new CDEvent(ParticleGointToLeaveSystem, tmpTime, particle, NULL, system->Bounds->TopRightPoint->X, -1);
            _eventsList->push_back(event);
        }
    }
    if (system->Bounds->TopRightPoint->Y == _height)
    {
        tmpTime = this->DetectCollisionBetweenParticleAndBound(particle, system->Bounds->TopRightPoint->Y, true);
        if (needToAdd)
        {
            CDEvent *event = new CDEvent(ParticleGointToLeaveSystem, tmpTime, particle, NULL, -1, system->Bounds->TopRightPoint->Y);
            _eventsList->push_back(event);
        }
    }
}

void CDParticlesCollisionDetection2DLogic::ComputeMinimalTimeOfCollision(int time)
{
}

void CDParticlesCollisionDetection2DLogic::ChangeVelocityAfterTwoParticleCollision(CDParticle2D *p1, CDParticle2D *p2)
{
	// TODO: need to implement
}

void CDParticlesCollisionDetection2DLogic::ChangeVelocityAfterParticlesCollisionWithBound(CDParticle2D *p, float bound)
{
	// TODO: need to implement
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
void CDParticlesCollisionDetection2DLogic::DecectCollisionBetweenParticlesInTime(int time)
{
	// If inequation is true - then make a computation
	// Else - skip computation
	unsigned long	eventsListSize = this->_eventsList->size();
	CDEvent			*nextEvent; // TODO: need to implement
	float			timeOfNextEvent = nextEvent->TimeToEvent;
	float			localTime = nextEvent->Particle1->LocalTime;

	if(fabs(time - (localTime + timeOfNextEvent)) < _eps)
	{

	}
	else if(eventsListSize == 0)
	{
		this->ComputeMinimalTimeOfCollision(time);
	}
}


