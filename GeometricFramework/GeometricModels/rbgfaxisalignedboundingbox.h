//
//  rbgfaxisalignedboundingbox.h
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/8/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef RBGFAXISALIGNEDBOUNDINGBOX_H
#define RBGFAXISALIGNEDBOUNDINGBOX_H
#include "rbgfboundingvolume.h"
#include "rbgfpoint.h"
#include "rbgfvector.h"

class RBGFAxisAlignedBoundingBox : public RBGFBoundingVolume
{
public:
    RBGFAxisAlignedBoundingBox(const RBGFPoint *center, double x, double y);
    RBGFAxisAlignedBoundingBox(const RBGFPoint *center, double x, double y, double z);
    const RBGFPoint* getCenter();
    const double* getDistances();
    int getDimension();
    
private:
    RBGFPoint *_center;
    double *_distances;      // array of distances in each dimention
    int _dimension;
};

#endif // RBGFAXISALIGNEDBOUNDINGBOX_H