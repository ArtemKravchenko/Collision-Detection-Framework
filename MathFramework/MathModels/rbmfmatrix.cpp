#include "rbmfmatrix.h"


// Constructors
RBMFMatrix::RBMFMatrix()
{
}
RBMFMatrix::RBMFMatrix(int countOfRow, int countOfCol, const double array[])
{
    _countOfRow = countOfRow;
    _countOfCol = countOfCol;
    _arraySize = _countOfRow * _countOfCol;
    _array = new double[_arraySize];
    for (int i = 0; i < _arraySize; i++) { _array[i] = array[i]; }
}
RBMFMatrix::~RBMFMatrix()
{
    delete []_array;
}
// Public methods
int RBMFMatrix::getCountOfRows()
{

}
int RBMFMatrix::getCountOfCols()
{

}
int RBMFMatrix::getCountOfElements()
{

}
double* RBMFMatrix::getElements() const
{

}
RBMFMatrix* RBMFMatrix::getTransponent() const
{
    double *transponentArray = new double[_arraySize];
    int k = 0;
    int offset = 0;
    for (int i = 0; i < _arraySize; i++)
    {
        if ((i + _countOfRow) % _countOfRow == 0)
        {
            transponentArray[i] = transponentArray[k++];
            offset = _countOfCol;
        }
        else
        {
            transponentArray[i] = transponentArray[(k-1) + offset];
            offset += _countOfCol;
        }
    }
    GUMatrix *returnMatrix = new GUMatrix(_countOfCol, _countOfRow, transponentArray);
    return returnMatrix;
}
