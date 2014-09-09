#ifndef RBMFUTILS_H
#define RBMFUTILS_H
#include "rbmfmatrix.h"
#include <array>

class RBMFUtils
{
private:
    int invCnt( int A[], int p, int r );
public:
    // Determinant
    double determinantOfTwoDimention(std::array<double, 4> elements);
    double determinantOfThreeDimention(std::array<double, 9> elements);
    double determinant(double *elements, int size, int square);
    // Singleton
    static RBMFUtils& sharedUtils()
    {
        static RBMFUtils utils;
        return utils;
    }
    RBMFUtils() {}
    RBMFUtils(RBMFUtils const&) {}              // Don't Implement.
    void operator=(RBMFUtils const&);           // Don't Implement.
};

#endif // RBMFUTILS_H
