#ifndef RBGFVECTOR_H
#define RBGFVECTOR_H
#include "rbgfpoint.h"

class RBGFVector
{
public:
    RBGFVector();
    ~RBGFVector();
    RBGFVector(RBGFPoint const *end); // bound vector
    RBGFVector(RBGFPoint const *start, RBGFPoint const *end); // free vector
    RBGFPoint& getStart();
    RBGFPoint& getEnd();
    double getLength();
    double dotProduct(RBGFVector *rhs);
    double dotProduct(RBGFPoint *rhs);
    RBGFVector& addVector(const RBGFVector& rhs);
    RBGFVector& subVector(const RBGFVector& rhs);
    RBGFVector& crossProduct(const RBGFVector& rhs);
private:
    RBGFPoint *_startPoint;
    RBGFPoint *_endPoint;
};

#endif // RBGFVECTOR_H
