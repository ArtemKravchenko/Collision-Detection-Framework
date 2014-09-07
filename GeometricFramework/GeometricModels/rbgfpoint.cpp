#include "rbgfpoint.h"

const int C_DIMENTION_2D = 2;
const int C_DIMENTION_3D = 3;
// Constructors
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
double* RBGFPoint::getCoordinates() const
{
    return _coordinates;
}
int RBGFPoint::getDimention()
{
    return _dimention;
}
// Operators
RBGFPoint RBGFPoint::operator+(RBGFPoint rhs)
{
    RBGFPoint lhs = *this;
    int dim = this->getDimention();
    if(dim != rhs.getDimention())
        return 0;
    double lhsEls[] = lhs.getCoordinates();
    double rhsEls[] = rhs.getCoordinates();
    double x = lhsEls[0] + rhsEls[0];
    double y = lhsEls[1] + rhsLls[1];
    if(dim == 2)
        return *(new RBGFPoint(x, y));
    double z = lhsEls[2] + rhsEls[2];
        return *(new RBGFPoint(x, y, z));
}
RBGFPoint RBGFPoint::operator-(RBGFPoint rhs)
{
    RBGFPoint lhs = *this;
    int dim = this->getDimention();
    if(dim != rhs.getDimention())
        return 0;
    double lhsEls[] = lhs.getCoordinates();
    double rhsEls[] = rhs.getCoordinates();
    double x = lhsEls[0] - rhsEls[0];
    double y = lhsEls[1] - rhsLls[1];
    if(dim == 2)
        return *(new RBGFPoint(x, y));
    double z = lhsEls[2] - rhsEls[2];
        return *(new RBGFPoint(x, y, z));
}
