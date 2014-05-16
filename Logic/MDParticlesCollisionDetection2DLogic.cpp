#include "MDParticlesCollisionDetection2DLogic.h"
#include "MDUtils.h"
#include <cmath>

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
MDParticlesCollisionDetection2DLogic::MDParticlesCollisionDetection2DLogic(MDParticlesList *particles, int width, int height, int countOfRows, int countOfCols)
{
	_actualCountOfSubsystems = countOfRows * countOfCols; _countOfRows = countOfRows;
	_countOfColumns = countOfCols;
	_subsystems = new MDSubsystemsList(_actualCountOfSubsystems); 
	_collisionPairs = new MDCollisionPairsList();
	this->InitSubsystems(particles);
	_subsystemWidth = width / countOfCols; 
	_subsystemHeight = height / countOfRows;
	_width = width;
	_height = height;
	_minTime = -1;
}

MDParticlesCollisionDetection2DLogic::~MDParticlesCollisionDetection2DLogic(void)
{
	_subsystems->clear();
	delete _subsystems;
	_subsystems = 0;
	
	_collisionPairs->clear();
	delete _collisionPairs;
	_collisionPairs = 0;
}
//--------------------------------------------------------------------
// Private functions
//--------------------------------------------------------------------
void MDParticlesCollisionDetection2DLogic::InitSubsystems(MDParticlesList *particles)
{
	int multiindexOfSystem;
	int countOfParticles = particles->size();
	// Init subsystems
	for(int i = 0; i < countOfParticles; i++)
	{
		MDParticle2D *particle = particles->at(i);
		multiindexOfSystem = MDUtils::GetMultiIndexOfSubsystem(static_cast<int>(particle->Position->X), static_cast<int>(particle->Position->Y), _subsystemWidth, _subsystemHeight, _countOfColumns);
		MDParticlesSystem *particleSystem = this->_subsystems->at(multiindexOfSystem);
		if(particleSystem == NULL)
		{
			particleSystem = new MDParticlesSystem();
		}
		particleSystem->AddParticle(particle);
	}
 
	// Init neighborhood
	int firstNeighbor, secondNeighbor, thirdNeighbor, fourthNeighbor;
	for(int i = 0; i < _actualCountOfSubsystems; i++)
	{
		MDParticlesSystem *particlesSystem = this->_subsystems->at(i);
		if(particlesSystem == NULL)
		{
			particlesSystem = new MDParticlesSystem();
			// Init system bounds
			particlesSystem->Bounds = new MDBounds();
			particlesSystem->Bounds->BottomLeftPoint = new MDVector2D(static_cast<float>(_subsystemWidth * i), static_cast<float>(_subsystemHeight * i));
			particlesSystem->Bounds->TopLeftPoint = new MDVector2D(static_cast<float>(_subsystemWidth * i), static_cast<float>(_subsystemHeight * i + _subsystemHeight));
			particlesSystem->Bounds->TopRightPoint = new MDVector2D(static_cast<float>(_subsystemWidth * i + _subsystemWidth), static_cast<float>(_subsystemHeight * i + _subsystemHeight));
			particlesSystem->Bounds->BottomRightPoint = new MDVector2D(static_cast<float>(_subsystemWidth * i + _subsystemWidth), static_cast<float>(_subsystemHeight * i));
		}
		std::vector<int> currentNeighborhood;//= new std::vector<int>();
		for(int j = 0; j < _countOfNeighborhood; j++)
		{
		// Init number of first neighbor
		firstNeighbor = j - _countOfColumns;
		if(firstNeighbor > 0) // if number of first neighbor isn't higer than upper bound
			currentNeighborhood.push_back(firstNeighbor);
		// Init number of second neighbor
		secondNeighbor = j + 1;
		if(secondNeighbor % _countOfColumns != 0) // if number of second neighbor isn't more right than right bound
			currentNeighborhood.push_back(secondNeighbor);
		// Init number of third neighbor
		thirdNeighbor = j + _countOfColumns;
		if(thirdNeighbor < _actualCountOfSubsystems)
		{
			currentNeighborhood.push_back(thirdNeighbor);
			// Init fourth neighbor
			fourthNeighbor = thirdNeighbor + 1;
			if(fourthNeighbor % _countOfColumns != 0)
			currentNeighborhood.push_back(fourthNeighbor);
		}
		MDNeighborhoodPair p = MDNeighborhoodPair(i, currentNeighborhood);
		_neighborhood->insert(p);
	}
 }
}

float MDParticlesCollisionDetection2DLogic::DetectCollisionBetweenTwoParticles(MDParticle2D *p1, MDParticle2D *p2)
{
	return 0; // TODO: need to implement
}

float MDParticlesCollisionDetection2DLogic::DetectCollisionBetweenParticleAndBound(MDParticle2D *p, int boundOrigin, bool isVerticalBound)
{
	return 0; // TODO: need to implement
}

void MDParticlesCollisionDetection2DLogic::AddCollisionPairToList(MDParticle2D *p1, MDParticle2D *p2, float xBound, float yBound, bool clearCollisionPairList)
{
	if(clearCollisionPairList)
	{
		this->_collisionPairs->clear();
	}
	MDCollisionPair *collisionPair = new MDCollisionPair();
	collisionPair->_firstParticle = p1;
	collisionPair->_secondParticle = p2;
	collisionPair->_xBound = xBound;
	collisionPair->_yBound = yBound;
	this->_collisionPairs->push_back(collisionPair);
}

void MDParticlesCollisionDetection2DLogic::TryAddCollsionPairToList(MDParticle2D *p1, MDParticle2D *p2, float xBound, float yBound)
{
	float tmpTime = -1;
	if(p2 != NULL)
		tmpTime = this->DetectCollisionBetweenTwoParticles(p1, p2);	
	else if(xBound != -1)
		tmpTime = this->DetectCollisionBetweenParticleAndBound(p1, static_cast<int>(xBound), false);
	else if(yBound != -1)
		tmpTime = this->DetectCollisionBetweenParticleAndBound(p1, static_cast<int>(yBound), true);

	if(_minTime == -1 || tmpTime < _minTime)
	{
		_minTime = tmpTime;
		this->AddCollisionPairToList(p1, p2, xBound, yBound, true);
	} 
	else if(abs(_minTime - tmpTime) < _eps)
	{	
		this->AddCollisionPairToList(p1, p2, xBound, yBound, false);
	}
}

void MDParticlesCollisionDetection2DLogic::ComputeMinimalTimeOfCollision(int time)
{
	_minTime = -1;
	MDParticle2D *tmpFirstParticle;
	MDParticle2D *tmpSecondParticle;
	MDParticlesSystem *tmpSystem;
	for(unsigned int i = 0; i <_subsystems->size(); i++)													// Loop through the subsystem
	{
		tmpSystem = _subsystems->at(i);
		for(unsigned int j = 0; j < tmpSystem->Particles->size(); j++)										// Loop through the each particle in subsystem
		{
			tmpFirstParticle = tmpSystem->Particles->at(j);
			for(unsigned int k = j + 1; k < tmpSystem->Particles->size(); k++)								// Compare particle with another particles in subsystem
			{
				tmpSecondParticle = tmpSystem->Particles->at(k);
				this->TryAddCollsionPairToList(tmpFirstParticle, tmpSecondParticle, -1, -1);
			}
			// Try to detect collision between particle and bounds
			// Detect collision between particle and bottom bound
			this->TryAddCollsionPairToList(tmpFirstParticle, NULL, -1, tmpSystem->Bounds->BottomLeftPoint->Y);
			// Detect collision between particle and left bound
			this->TryAddCollsionPairToList(tmpFirstParticle, NULL, tmpSystem->Bounds->BottomLeftPoint->X, -1);
			// Detect collision between particle and upper bound
			this->TryAddCollsionPairToList(tmpFirstParticle, NULL, -1, tmpSystem->Bounds->TopRightPoint->Y);
			// Detect collision between particle and right bound
			this->TryAddCollsionPairToList(tmpFirstParticle, NULL, tmpSystem->Bounds->TopRightPoint->X, -1);
		}
	}
}

void MDParticlesCollisionDetection2DLogic::ChangeVelocityAfterTwoParticleCollision(MDParticle2D *p1, MDParticle2D *p2)
{
	// TODO: need to implement
}

void MDParticlesCollisionDetection2DLogic::ChangeVelocityAfterParticlesCollisionWithBound(MDParticle2D *p, float bound)
{
	// TODO: need to implement
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
void MDParticlesCollisionDetection2DLogic::DecectCollisionBetweenParticlesInTime(int time)
{
	// If inequation is true - then make a computation
	// Else - skip computation
	unsigned int collisionPairSize = _collisionPairs->size();
	for(unsigned int i = 0; i < collisionPairSize; i++)
	{
		MDCollisionPair *collisionPair = _collisionPairs->at(i);
		if(_minTime >= 0  &&  abs(time - collisionPair->_firstParticle->LocalTime + _minTime))
		{
			// Change veclocity of particles that includes in collision pair
			if(collisionPair->_secondParticle != NULL)
			{
				this->ChangeVelocityAfterTwoParticleCollision(collisionPair->_firstParticle, collisionPair->_secondParticle);
			}
			else 
			{
				if(collisionPair->_xBound != -1)
				{
					if(collisionPair->_xBound > 0 && collisionPair->_xBound < this->_width)
					{
					// TODO: particle change the subsystem
					}
					else {
						this->ChangeVelocityAfterParticlesCollisionWithBound(collisionPair->_firstParticle, collisionPair->_xBound);
					}
				}
				if(collisionPair->_yBound != -1)
				{
					this->ChangeVelocityAfterParticlesCollisionWithBound(collisionPair->_firstParticle, collisionPair->_yBound);
				}
			}
			// Need to recompute minimal time of collision
			this->ComputeMinimalTimeOfCollision(time);
		}
	}
}
