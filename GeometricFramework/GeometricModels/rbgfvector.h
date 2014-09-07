#ifndef RBGFVECTOR_H
#define RBGFVECTOR_H
#include "rbgfpoint.h"

class RBGFVector
{
public:
    RBGFVector();
    ~RBGFVector();
    RBGFVector(RBGFPoint *end); // bound vector
    RBGFVector(RBGFPoint *start, RBGFPoint *end); // free vector
    RBGFPoint* getStart() const;
    RBGFPoint* getEnd() const;
    double getLength();
    double dotProduct(RBGFPoint *rhs);
    RBGFVector& operator+(const RBGFVector& rhs);
    RBGFVector& operator-(const RBGFVector& rhs);
    RBGFVector& operator*(const RBGFVector& rhs);
private:
    RBGFPoint* _startPoint;
    RBGFPoint* _endPoint;
};

#endif // RBGFVECTOR_H
