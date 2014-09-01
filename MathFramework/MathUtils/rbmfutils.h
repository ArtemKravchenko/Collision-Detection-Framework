#ifndef RBMFUTILS_H
#define RBMFUTILS_H
#include "rbmfmatrix.h"

class RBMFUtils
{
public:
    RBMFUtils();
    static RBMFMatrix* addTwoMatrix(RBMFMatrix* matrix1, RBMFMatrix* matrix2);
};

#endif // RBMFUTILS_H
