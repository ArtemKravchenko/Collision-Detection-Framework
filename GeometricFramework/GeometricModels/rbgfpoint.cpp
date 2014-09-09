#include "rbgfpoint.h"

RBGFPoint::RBGFPoint()
{
    _coordinates = nullptr;
    _dimention = 0;
}
RBGFPoint::RBGFPoint(double x, double y)
{
    _coordinates = new double[C_DIMENTION_2D] {x, y};
    _dimention = C_DIMENTION_2D;
}
RBGFPoint::RBGFPoint(double x, double y, double z)
{
    _coordinates = new double[C_DIMENTION_3D] {x, y, z};
    _dimention = C_DIMENTION_3D;
}
// Public function
const double* RBGFPoint::getCoordinates() const
{
    return _coordinates;
}
int RBGFPoint::getDimention() const
{
    return _dimention;
}
RBGFPoint* RBGFPoint::productByNumber(double num)
{
    if (_dimention == C_DIMENTION_2D)
        return new RBGFPoint(_coordinates[0] * num, _coordinates[1] * num);
    else
        return new RBGFPoint(_coordinates[0] * num, _coordinates[1] * num, _coordinates[2] * num);
}
// Operators
RBGFPoint& RBGFPoint::operator+(const RBGFPoint& rhs)
{
    RBGFPoint *lhs = this;
    int dim = getDimention();
    if(dim != rhs.getDimention())
        return *new RBGFPoint();
    const double *lhsEls = lhs->getCoordinates();
    const double *rhsEls = rhs.getCoordinates();
    double x = lhsEls[0] + rhsEls[0];
    double y = lhsEls[1] + rhsEls[1];
    if(dim == 2)
        return *(new RBGFPoint(x, y));
    double z = lhsEls[2] + rhsEls[2];
    return *(new RBGFPoint(x, y, z));
}
RBGFPoint& RBGFPoint::operator-(const RBGFPoint& rhs)
{
    RBGFPoint lhs = *this;
    int dim = getDimention();
    if(dim != rhs.getDimention())
        return *new RBGFPoint();;
    const double *lhsEls = lhs.getCoordinates();
    const double *rhsEls = rhs.getCoordinates();
    double x = lhsEls[0] - rhsEls[0];
    double y = lhsEls[1] - rhsEls[1];
    if(dim == 2)
        return *(new RBGFPoint(x, y));
    double z = lhsEls[2] - rhsEls[2];
    return *(new RBGFPoint(x, y, z));
}