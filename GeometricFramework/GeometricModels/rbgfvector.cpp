#include "rbgfvector.h"
#include <math.h>
#include "rbmfutils.h"
#include "float.h"
#include <iostream>

// Constructors and destuctors
RBGFVector::RBGFVector()
{
    std::cout << "";
    _startPoint = new RBGFPoint(0, 0);
    _endPoint = new RBGFPoint(0, 0);
}
RBGFVector::RBGFVector(RBGFPoint const * end)
{
    if (end != NULL) {
        if(end->getDimention() == 2)
        {
            _startPoint = new RBGFPoint(0, 0);
            const double *els = end->getCoordinates();
            _endPoint = new RBGFPoint(els[0], els[1]);
        }
        else
        {
            _startPoint = new RBGFPoint(0, 0, 0);
            const double *els = end->getCoordinates();
            _endPoint = new RBGFPoint(els[0], els[1], els[2]);
        }
    }
}
RBGFVector::RBGFVector(RBGFPoint const * start, RBGFPoint const * end)
{
    if (start->getDimention() == end->getDimention()) {
        if (end->getDimention() == 2) {
            const double *els = start->getCoordinates();
            _startPoint = new RBGFPoint(els[0], els[1]);
            els = end->getCoordinates();
            _endPoint = new RBGFPoint(els[0], els[1]);
        } else {
            const double *els = start->getCoordinates();
            _startPoint = new RBGFPoint(els[0], els[1], els[2]);
            els = end->getCoordinates();
            _endPoint = new RBGFPoint(els[0], els[1], els[2]);
        }
    }
}
RBGFVector::~RBGFVector()
{
    delete _startPoint;
    delete _endPoint;
}
// Public functions
RBGFPoint& RBGFVector::getStart()
{
    return *_startPoint;
}
RBGFPoint& RBGFVector::getEnd()
{
    return *_endPoint;
}
double RBGFVector::getLength()
{
    double retValue = 0;
    int length = _startPoint->getDimention();
    const double *startEls = _startPoint->getCoordinates();
    const double *endEls = _endPoint->getCoordinates();
    for(int i = 0; i < length; i++)
    {
        retValue += (endEls[i] - startEls[i]) * (endEls[i] - startEls[i]);
    }
    return sqrt(retValue);
}
double RBGFVector::dotProduct(RBGFVector *rhs)
{
    RBGFPoint rhsP = rhs->getEnd() - rhs->getStart();
    RBGFPoint lhsP = *_endPoint - *_startPoint;
    const double *lhsEls = lhsP.getCoordinates();
    const double *rhsEls = rhsP.getCoordinates();
    int dim = rhsP.getDimention();
    if (dim != lhsP.getDimention())
        return DBL_MIN;
    double ret = 0;
    for (int i = 0; i < dim; i++)
        ret += lhsEls[i]*rhsEls[i];
    delete &rhsP;
    delete &lhsP;
    return ret;
}
double RBGFVector::dotProduct(RBGFPoint *rhs)
{
    RBGFPoint lhsP = *_endPoint - *_startPoint;
    const double *lhsEls = lhsP.getCoordinates();
    const double *rhsEls = rhs->getCoordinates();
    int dim = rhs->getDimention();
    if (dim != lhsP.getDimention())
        return DBL_MIN;
    double ret = 0;
    for (int i = 0; i < dim; i++)
        ret += lhsEls[i]*rhsEls[i];
    delete  &lhsP;
    return ret;
}
// Operators
RBGFVector& RBGFVector::addVector(const RBGFVector& rhs)
{
    RBGFPoint startPoint = getStart() + *rhs._startPoint;
    RBGFPoint endPoint = getEnd() + *rhs._endPoint;
    RBGFVector *ret = new RBGFVector(&startPoint, &endPoint);
    delete &startPoint;
    delete &endPoint;
    return *ret;
}
RBGFVector& RBGFVector::subVector(const RBGFVector& rhs)
{
    RBGFPoint startPoint = getStart() - *rhs._startPoint;
    RBGFPoint endPoint = getEnd() - *rhs._endPoint;
    RBGFVector *ret = new RBGFVector(&startPoint, &endPoint);
    delete &startPoint;
    delete &endPoint;
    return *ret;
}
RBGFVector& RBGFVector::crossProduct(const RBGFVector& rhs)
{
    if(rhs._endPoint->getDimention() != 3)
        return *new RBGFVector();
    RBGFPoint lhsPoint = getEnd() - getStart();
    RBGFPoint p1 = *rhs._endPoint;
    RBGFPoint p2 = *rhs._startPoint;
    RBGFPoint rhsPoint = p1 - p2;
    const double *lhsEls = lhsPoint.getCoordinates();
    const double *rhsEls = rhsPoint.getCoordinates();
    RBMFUtils utils = RBMFUtils::sharedUtils();
    std::array<double,4> xEls = {lhsEls[1], lhsEls[2], rhsEls[1], rhsEls[2]};
    double x = utils.determinantOfTwoDimention(xEls);
    std::array<double,4> yEls = {lhsEls[0], lhsEls[2], rhsEls[0], rhsEls[2]};
    double y = -utils.determinantOfTwoDimention(yEls);
    std::array<double,4> zEls = {lhsEls[0], lhsEls[1], rhsEls[0], rhsEls[1]};
    double z = utils.determinantOfTwoDimention(zEls);
    const double *startCoordinates = getStart().getCoordinates();
    RBGFPoint *start = new RBGFPoint(startCoordinates[0], startCoordinates[1], startCoordinates[2]);
    RBGFVector *ret = new RBGFVector(start, new RBGFPoint(x, y, z));
    delete &lhsPoint;
    delete &rhsPoint;
    delete start;
    return *ret;
}
