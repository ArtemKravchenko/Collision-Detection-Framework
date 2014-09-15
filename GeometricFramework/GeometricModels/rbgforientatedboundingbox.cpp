#include "rbgforientatedboundingbox.h"

// Constructors
RBGFOrientatedBoundingBox::RBGFOrientatedBoundingBox()
{
}
RBGFOrientatedBoundingBox::RBGFOrientatedBoundingBox(RBGFPoint * const center, RBGFVector * const localAxis[3], RBGFVector * const halfwidth)
{
    _center = new RBGFPoint(*center);
    _localAxis = new RBGFVector[3];
    _localAxis[0] = new RBGFVector(*localAxis[0]);
    _localAxis[1] = new RBGFVector(*localAxis[1]);
    _localAxis[2] = new RBGFVector(*localAxis[2]);
    _localAxis = new RBGFVector(*halfwidth);
}
// Public methods
RBGFPoint const RBGFOrientatedBoundingBox::getCenter()
{
    return _center;
}
RBGFVector* const RBGFOrientatedBoundingBox::getLocalAxis()
{
    return _localAxis;
}
RBGFVector* const RBGFOrientatedBoundingBox::getHalfWidth()
{
    return _halfwidth;
}
void RBGFOrientatedBoundingBox::setCenter(RBGFPoint * const point) const
{
    _center = new RBGFPoint(*point);
}
void RBGFOrientatedBoundingBox::setLocalAxis(RBGFVector * const localAxis[3]) const
{
    if(localAxis != nullptr)
        delete localAxis;

    _localAxis = new RBGFVector[3];
    _localAxis[0] = new RBGFVector(*localAxis[0]);
    _localAxis[1] = new RBGFVector(*localAxis[1]);
    _localAxis[2] = new RBGFVector(*localAxis[2]);
}
void RBGFOrientatedBoundingBox::setHalfWidth(RBGFVector * const halfwidth) const
{
    _localAxis = new RBGFVector(*halfwidth);
}
