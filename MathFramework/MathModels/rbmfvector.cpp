#include "rbmfvector.h"
#include "float.h"

// Constructors
RBMFVector::RBMFVector()
{
}
RBMFVector::RBMFVector(int dimention, const double elements[])
{
    elements = new double();
    _dimention = dimention;
    _elements = new double[_dimention];
    for(int i = 0; i < _dimention; i++)
        _elements[i] = elements[i];
}
RBMFVector::~RBMFVector()
{
    delete[] _elements;
    _elements = nullptr;
}
// Public functions
const double* RBMFVector::getElements() const
{
    return _elements;
}
int RBMFVector::getDimention()
{
    return _dimention;
}
double RBMFVector::dotProduct(RBMFVector *rhs)
{
    if (this->_dimention != rhs->_dimention)
        return DBL_MIN;
    double ret = 0;
    for (int i = 0; i < _dimention; i++)
        ret += (_elements[i])*(rhs->_elements[i]);
    return ret;
}
