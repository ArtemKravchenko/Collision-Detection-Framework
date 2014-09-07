#include "rbmfmatrix.h"


// Constructors
RBMFMatrix::RBMFMatrix()
{
    _countOfRows = 0;
    _countOfCols = 0;
    _dimention = _countOfRows * _countOfCols;
    _elements = new double[_dimention];
}
RBMFMatrix::RBMFMatrix(int countOfRow, int countOfCol, const double array[])
{
    _countOfRows = countOfRow;
    _countOfCols = countOfCol;
    _dimention = _countOfRows * _countOfCols;
    _elements = new double[_dimention];
    for (int i = 0; i < _dimention; i++) { _elements[i] = array[i]; }
}
RBMFMatrix::~RBMFMatrix()
{
    delete []_array;
}
// Operators
RBMFMatrix RBMFMatrix::operator+(RBMFMatrix rhs)
{
    RBMFMatrix lhs = *this;
    if (lhs.getCountOfRows() != rhs.getCountOfRows() || lhs.getCountOfCols() != rhs.getCountOfCols())
        return *(new RBMFMatrix());
    int size = lhs.getCountOfElements();
    double *elements = new double[size];
    double *lhsElements = lhs.getElements();
    double *rhsElements = rhs.getElements();
    for (int i = 0; i < size; i++)
    {
        elements[i] = lhsElements[i] + rhsElements[i];
    }
    RBMFMatrix *retMatrix = new RBMFMatrix(lhs.getCountOfRows(), lhs.getCountOfCols(), elements);
    return *retMatrix;
}
RBMFMatrix RBMFMatrix::operator*(RBMFMatrix rhs)
{
    RBMFMatrix lhs = *this;
    if (lhs.getCountOfCols() != rhs.getCountOfRows())
        return *(new RBMFMatrix());
    int innerCount = lhs.getCountOfCols();
    int countOfCols = rhs.getCountOfCols();
    int countOfRows = lhs.getCountOfRows();
    double *lhsElements = lhs.getElements();
    double *rhsElements = rhs.getElements();
    int elementsSize = countOfCols * countOfRows;
    double *elements = new double[elementsSize];
    double partialSum;
    for(int i = 0; i < countOfRows; i++)
    {
        for(int j = 0; j < countOfCols; j++)
        {
            partialSum = 0;
            for(int k = 0; k < innerCount; k++)
            {
                partialSum += lhsElements[k + i * countOfCols] * rhsElements[k * countOfCols + j];
            }
            elements[i*countOfCols + j] = partialSum;
        }
    }
    RBMFMatrix *retMatrix = new RBMFMatrix(countOfRows, countOfCols, elements);
    return *retMatrix;
}
// Public methods
int RBMFMatrix::getCountOfRows()
{
    return _countOfRows;
}
int RBMFMatrix::getCountOfCols()
{
    return _countOfCols;
}
int RBMFMatrix::getCountOfElements()
{
    return _dimention;
}
double* RBMFMatrix::getElements() const
{
    return _elements;
}
RBMFMatrix* RBMFMatrix::getTransponent()
{
    double *transponentArray = new double[_dimention];
    int k = 0;
    int offset = 0;
    for (int i = 0; i < _dimention; i++)
    {
        if ((i + _countOfRows) % _countOfRows == 0)
        {
            transponentArray[i] = _elements[k++];
            offset = _countOfCols;
        }
        else
        {
            transponentArray[i] = _elements[(k-1) + offset];
            offset += _countOfCols;
        }
    }
    RBMFMatrix *returnMatrix = new RBMFMatrix(_countOfCols, _countOfRows, transponentArray);
    return returnMatrix;
}

RBMFMatrix* RBMFMatrix::productByNumber(double number)
{
    double *elements = new double[_dimention];
    for (int i = 0; i < _dimention; i++) { elements[i] = _elements[i] * number; }
    RBMFMatrix *retMatrix = new RBMFMatrix(_countOfRows, _countOfCols, elements);
    return retMatrix;
}
