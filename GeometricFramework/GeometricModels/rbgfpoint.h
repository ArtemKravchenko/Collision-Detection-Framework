#ifndef RBGFPOINT_H
#define RBGFPOINT_H

class RBGFPoint
{
public:
    RBGFPoint();
    RBGFPoint(double x, double y); // Initialize 2D point
    RBGFPoint(double x, double y, double z); // Initialize 3D point
    double* getCoordinates() const;
    int getDimention();
    RBGFPoint RBGFPoint::operator+(RBGFPoint rhs);
    RBGFPoint RBGFPoint::operator-(RBGFPoint rhs);

private:
    double *_coordinates;
    int _dimention;
};

#endif // RBGFPOINT_H
