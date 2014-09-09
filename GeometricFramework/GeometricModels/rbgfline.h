//
//  rbgfline.h
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/7/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef RBGFLINE_H
#define RBGFLINE_H
#include "rbgfpoint.h"

class RBGFLine
{
public:
    RBGFLine();
    ~RBGFLine();
    RBGFLine(RBGFPoint *p1, RBGFPoint *p2);
    const RBGFPoint* getPointFromLine(double t);
private:
    RBGFPoint *_firstPoint;
    RBGFPoint *_secondPoint;
};

#endif // RBGFLINE_H