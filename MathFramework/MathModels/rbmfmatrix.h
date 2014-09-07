#ifndef RBMFMATRIX_H
#define RBMFMATRIX_H
#include "rbmfvector.h"

class RBMFMatrix : public RBMFVector
{
public:
    RBMFMatrix();
    ~RBMFMatrix();
    RBMFMatrix(int countOfRow, int countOfCol, const double array[]);
    int getCountOfRows();
    int getCountOfCols();
    int getCountOfElements();
    double* getElements() const;
    RBMFMatrix* getTransponent();
    RBMFMatrix* productByNumber(double number);
    RBMFMatrix operator+(RBMFMatrix rhs);
    RBMFMatrix operator*(RBMFMatrix rhs);

private:
    int _countOfRows;
    int _countOfCols;
    double *_array;
};

#endif // RBMFMATRIX_H
