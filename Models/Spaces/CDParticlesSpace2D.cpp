
#include "CDParticlesSpace2D.h"
#include "CDUtils.h"

//--------------------------------------------------------------------
// Constructor and destructors
//--------------------------------------------------------------------
CDParticlesSpace2D::CDParticlesSpace2D(CDParticlesList *particles, int width, int height)
{
	_particles = particles;

	int countOfRows;
	int *ptrCountOfRows = &countOfRows;
	int countOfColumns;
	int *ptrCountOfColumns = &countOfColumns;
	CDUtils::GetCountOfRowsAndColumnsForParticlesCount(ptrCountOfRows, ptrCountOfColumns, static_cast<int>(particles->size()));
	_collisionDetectionLogic = new CDParticlesCollisionDetection2DLogic(particles, width, height, countOfRows, countOfColumns);
	_physicLogic = new CDParticlesPhysicLogic(particles);
	_width = width;
	_height = height;
}


CDParticlesSpace2D::~CDParticlesSpace2D(void)
{
}
//--------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------
 void CDParticlesSpace2D::MoveParticlesInSpaceInTime(int time)
{
	_collisionDetectionLogic->DecectCollisionBetweenParticlesInTime(time);
	_physicLogic->MoveParticlesInSpace2DInTime(time);
}