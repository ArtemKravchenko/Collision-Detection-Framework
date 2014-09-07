#include "rbgfvector.h"
#include <math.h>
#include "rbmfutils.h"
// Constructors and destuctors
RBGFVector::RBGFVector()
{
}
RBGFVector::RBGFVector(RBGFPoint* end)
{
    if(end->getDimention() == 2)
        _startPoint = new RBGFPoint(0, 0);
    else
        _startPoint = new RBGFPoint(0, 0, 0);
    _endPoint = new Point();
    *_endPoint = *end;
}
RBGFVector::RBGFVector(RBGFPoint* start, RBGFPoint* end)
{
    _startPoint = new Point();
    *_startPoint = *start;
    _endPoint = new Point();
    *_endPoint = *end;
}
RBGFVector::~RBGFVector()
{
    delete _startPoint;
    _startPoint = nullptr;
    delete _endPoint;
    _endPoint = nullptr;
}
// Public functions
RBGFPoint* RBGFVector::getStart() const
{
    return _startPoint;
}
RBGFPoint* RBGFVector::getEnd() const
{
    return _endPoint;
}
double RBGFVector::getLength()
{
    double retValue = 0;
    int length = _startPoint->getDimention();
    double startEls[] = _startPoint->getCoordinates();
    double endEls[] = _endPoint->getCoordinates();
    for(int i = 0; i < length; i++)
    {
        retValue += (endEls[i] - startEls[i]) * (endEls[i] - startEls[i]);
    }
    return sqrt(retValue);
}
double RBGFVector::dotProduct(RBGFPoint *rhs)
{
    RBGFVector *
}
// Operators
RBGFVector& RBGFVector::operator+(const RBGFVector& rhs)
{
    RBGFVector lhs = *this;
    RBGFPoint startPoint = lhs.getStart() + rhs.getStart();
    RBGFPoint endPoint = lhs.getEnd() + rhs.getEnd();
    return *(new RBGFVector(startPoint, endPoint));
}
RBGFVector& RBGFVector::operator-(const RBGFVector& rhs)
{
    RBGFVector lhs = *this;
    RBGFPoint startPoint = lhs.getStart() - rhs.getStart();
    RBGFPoint endPoint = lhs.getEnd() - rhs.getEnd();
    return *(new RBGFVector(startPoint, endPoint));
}
RBGFVector& RBGFVector::operator*(const RBGFVector& rhs)
{
    if(rhs.getEnd()->getDimention() != 3)
        return 0;
    RBGFVector lhs = *this;
    RBGFPoint *lhsPoint = lhs.getEnd() - lhs.getStart();
    RBGFPoint *rhsPoint = rhs.getEnd() - lhs.getStart();
    double lhsEls[] = lhsPoint->getCoordinates();
    double rhsEls[] = rhsPoint->getCoordinates();
    RBMFUtils *utils = RBMFUtils::sharedUtils();
    std::array<double,4> xEls = {lhsEls[1], lhsEls[2], rhsEls[1], rhsEls[2]};
    double x = utils->determinantOfTwoDimention(xEls);
    std::array<double,4> yEls = {lhsEls[0], lhsEls[2], rhsEls[0], rhsEls[2]};
    double y = utils->determinantOfTwoDimention(yEls);
    std::array<double,4> zEls = {lhsEls[0], lhsEls[1], rhsEls[0], rhsEls[1]};
    double z = utils->determinantOfTwoDimention(zEls);
    return new RBGFVector(lhs.getStart(), new RBGFPoint(x, y, z));
}
