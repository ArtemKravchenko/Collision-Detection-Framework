#ifndef RBGFORIENTATEDBOUNDINGBOX_H
#define RBGFORIENTATEDBOUNDINGBOX_H
#include "rbgfaxisalignedboundingbox.h"

class RBGFOrientatedBoundingBox : public RBGFAxisAlignedBoundingBox
{
public:
    RBGFOrientatedBoundingBox();
    RBGFOrientatedBoundingBox(RBGFPoint * const center, RBGFVector * const localAxis[3], RBGFVector * const halfwidth);
    RBGFPoint const getCenter();
    RBGFVector* const getLocalAxis();
    RBGFVector* const getHalfWidth();
    void setCenter(RBGFPoint * const point) const;
    void setLocalAxis(RBGFVector * const localAxis[3]) const;
    void setHalfWidth(RBGFVector * const halfwidth) const;
private:
    RBGFPoint   *_center; // OBB center point RBGF
    RBGFVector * _localAxis[3]; // Local x-, y-, and z-axes
    RBGFVector  *_halfwidth; // Positive halfwidth extents of OBB along each axis
};

#endif // RBGFORIENTATEDBOUNDINGBOX_H
