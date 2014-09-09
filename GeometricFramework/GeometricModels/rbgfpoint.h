#ifndef RBGFPOINT_H
#define RBGFPOINT_H
#include "float.h"
const int C_DIMENTION_2D = 2;
const int C_DIMENTION_3D = 3;
// Constructors

class RBGFPoint
{
public:
    RBGFPoint();
    RBGFPoint(double x, double y); // Initialize 2D point
    RBGFPoint(double x, double y, double z); // Initialize 3D point
    const double* getCoordinates() const;
    int getDimention() const;
    RBGFPoint* productByNumber(double num);
    RBGFPoint& operator+(const RBGFPoint& rhs);
    RBGFPoint& operator-(const RBGFPoint& rhs);

private:
    double *_coordinates;
    int _dimention;
};

#endif // RBGFPOINT_H
