#include "MDAbstractSystem.h"


MDAbstractSystem::MDAbstractSystem(MDVector2D *blp, MDVector2D *tlp, MDVector2D *trp, MDVector2D *brp)
{
	Bounds = new MDBounds(blp, tlp, trp, brp);
}

MDAbstractSystem::MDAbstractSystem()
{

}

MDAbstractSystem::~MDAbstractSystem(void)
{
	delete Bounds;
	Bounds = 0;
}
