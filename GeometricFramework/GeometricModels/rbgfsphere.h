//
//  rbgfsphere.h
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/8/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef RBGFSPHERE_H
#define RBGFSPHERE_H
#include "rbgfpoint.h"

class RBGFSphere
{
public:
    RBGFSphere(RBGFPoint * const center, double radius);
    const RBGFPoint* getCenter();
    double getRadius();
    void setRadius(double radius);
    void setCenter(RBGFPoint const *center);
private:
    RBGFPoint *_center;
    double _radius;
};

#endif // RBGFSPHERE_H