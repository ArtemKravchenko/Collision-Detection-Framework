#include "rbmfvector.h"

// Constructors
RBMFVector::RBMFVector()
{
}
RBMFVector::RBMFVector(int dimention, const double* elements)
{
    elements = new double();
    _dimention = dimention;
    _elements = new double[_dimention];
    for(int i = 0; i < _dimention; i++)
        _elements[i] = elements;
}
RBMFVector::~RBMFVector()
{
    delete[] _elements;
}
// Public functions
double RBMFVector::getElements() const
{
    return _elements;
}
int RBMFVector::getDimention() const
{
    return _dimention;
}
