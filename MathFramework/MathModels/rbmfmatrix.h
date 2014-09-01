#ifndef RBMFMATRIX_H
#define RBMFMATRIX_H
#include "rbmfvector.h";

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
    RBMFMatrix* getTransponent() const;

private:
    int _countOfRow;
    int _countOfCol;
    int _arraySize;
    double *_array;
};

#endif // RBMFMATRIX_H
