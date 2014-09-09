//
//  rbgfsphere.cpp
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/8/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#include "rbgfsphere.h"
#include <stdio.h>

// Constructors
RBGFSphere::RBGFSphere(RBGFPoint * const center, double radius)
{
    _center = new RBGFPoint(*center);
    _radius = radius;
}
// Public functions
const RBGFPoint* RBGFSphere::getCenter()
{
    return _center;
}
double RBGFSphere::getRadius()
{
    return _radius;
}
void RBGFSphere::setRadius(double radius)
{
    _radius = radius;
}
void RBGFSphere::setCenter(RBGFPoint const *center)
{
    if (_center != nullptr) {
        delete _center;
    }
    _center = new RBGFPoint(*center);
}