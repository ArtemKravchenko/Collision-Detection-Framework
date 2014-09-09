//
//  rbgfaxisalignedboundingbox.cpp
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/8/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#include "rbgfaxisalignedboundingbox.h"
#include <stdio.h>
#include <stdlib.h>

// Constructors
RBGFAxisAlignedBoundingBox::RBGFAxisAlignedBoundingBox(const RBGFPoint * const center, double x, double y)
{
    _center = new RBGFPoint(*center);
    _dimension = C_DIMENTION_2D;
    _distances = new double[_dimension] {x , y};
    
}

RBGFAxisAlignedBoundingBox::RBGFAxisAlignedBoundingBox(const RBGFPoint * const center, double x, double y, double z)
{
    _center = new RBGFPoint(*center);
    _dimension = C_DIMENTION_3D;
    _distances = new double[_dimension] {x , y, z};
    
}
// Public functions
const RBGFPoint* RBGFAxisAlignedBoundingBox::getCenter()
{
    return _center;
}
const double* RBGFAxisAlignedBoundingBox::getDistances()
{
    return _distances;
}
int RBGFAxisAlignedBoundingBox::getDimension()
{
    return _dimension;
}