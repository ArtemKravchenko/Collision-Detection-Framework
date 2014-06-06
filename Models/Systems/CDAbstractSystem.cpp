#include "CDAbstractSystem.h"


CDAbstractSystem::CDAbstractSystem(CDVector2D *blp, CDVector2D *tlp, CDVector2D *trp, CDVector2D *brp)
{
	Bounds = new CDBounds(blp, tlp, trp, brp);
}

CDAbstractSystem::CDAbstractSystem()
{

}

CDAbstractSystem::~CDAbstractSystem(void)
{
	delete Bounds;
	Bounds = 0;
}
