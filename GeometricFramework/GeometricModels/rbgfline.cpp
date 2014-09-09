//
//  rbgfline.cpp
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 9/7/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#include "rbgfline.h"
// Constructors
RBGFLine::RBGFLine()
{
}
RBGFLine::~RBGFLine()
{

}
RBGFLine::RBGFLine(RBGFPoint *p1, RBGFPoint *p2)
{
    if (p1 != nullptr && p2 != nullptr) {
        if (p1->getDimention() == p2->getDimention()) {
            int dim = p1->getDimention();
            const double *els;
            if (dim == 2) {
                els = p1->getCoordinates();
                _firstPoint = new RBGFPoint(els[0], els[1]);
                els = p2->getCoordinates();
                _secondPoint = new RBGFPoint(els[0], els[1]);
            } else {
                els = p1->getCoordinates();
                _firstPoint = new RBGFPoint(els[0], els[1], els[2]);
                els = p2->getCoordinates();
                _secondPoint = new RBGFPoint(els[0], els[1], els[2]);
            }
        }
    }
}
// Public functions
const RBGFPoint* RBGFLine::getPointFromLine(double t)
{
    return &(*(_firstPoint->productByNumber(1-t)) + *(_secondPoint->productByNumber(t)));
}