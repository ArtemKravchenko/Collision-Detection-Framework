
#include "MDParticlesSpace2D.h"
#include "MDUtils.h"

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
MDParticlesSpace2D::MDParticlesSpace2D(MDParticlesList *particles, int width, int height)
{
	_particles = particles;

	int countOfRows;
	int *ptrCountOfRows = &countOfRows;
	int countOfColumns;
	int *ptrCountOfColumns = &countOfColumns;
	MDUtils::GetCountOfRowsAndColumnsForParticlesCount(ptrCountOfRows, ptrCountOfColumns, static_cast<int>(particles->size()));
	_collisionDetectionLogic = new MDParticlesCollisionDetection2DLogic(particles, width, height, countOfRows, countOfColumns);
	_physicLogic = new MDParticlesPhysicLogic(particles);
	_width = width;
	_height = height;
}


MDParticlesSpace2D::~MDParticlesSpace2D(void)
{
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
 void MDParticlesSpace2D::MoveParticlesInSpaceInTime(int time)
{
	_collisionDetectionLogic->DecectCollisionBetweenParticlesInTime(time);
	_physicLogic->MoveParticlesInSpace2DInTime(time);
}