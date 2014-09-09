#include "rbmfutils.h"
#include <iostream>
#include <algorithm>
#include "float.h"
using namespace std;

// Public functions
double RBMFUtils::determinantOfTwoDimention(std::array<double, 4> elements)
{
    return elements[0] * elements[3] - elements[1]*elements[2];
}
double RBMFUtils::determinantOfThreeDimention(std::array<double, 9> elements)
{
    return elements[0]*elements[4]*elements[8] - elements[0]*elements[5]*elements[7] - elements[1]*elements[3]*elements[8] +
            elements[1]*elements[5]*elements[6] + elements[2]*elements[3]*elements[7] - elements[2]*elements[4]*elements[6];
}

double RBMFUtils::determinant(double *elements, int size, int square)
{
    if(square * square != size) return DBL_MIN;
    int* indexes = new int[square];
    for(int i = 0; i < square; i++) indexes[i] = i;
    double sum = 0;
    double part = 1;
    do {
        std::cout << endl;
        std::cout << "|" ;
        for (int i = 0; i < square; i++)
        {
            int index = i * square + indexes[i];
            std::cout << index;
            if(i != square - 1)
                std::cout << " ";
            part*=elements[index];
        }
        std::cout << "|" ;
        std::cout << "=" << part;
        std::cout << '\n';
        // Workaround
        int *dest = new int[square];
        for (int i = 0; i < square; i++) dest[i] = indexes[i];
        int countOfInversion = invCnt(dest, 0, square - 1);
        //
        if(countOfInversion % 2 == 0)
            sum += part;
        else
            sum -= part;
        std::cout << "sum " << sum << " ";
        part = 1;
        delete[] dest;
    } while ( std::next_permutation(indexes,indexes+square) );
    delete[] indexes;
    std::cout << endl;
    return sum;
}
// Private functions
int RBMFUtils::invCnt( int A[], int p, int r )
{
        int cnt = 0;
        int n = r - p + 1;
        int l1 = p;
        int r1 = p + n/2 -1;
        int l2 = p + n/2;
        int r2 = r;
        int *B = (int*)malloc( sizeof(int)*n );

        if( n <= 1 ) return 0;

        cnt += invCnt( A, l1, r1 );
        cnt += invCnt( A, l2, r2 );

        while( l1 <= r1 && l2 <= r2 ) {
                if( A[r1] < A[r2] ) {
                        B[--n] = A[r2--];
                } else {
                        B[--n] = A[r1--];
                        cnt += r2 - l2 + 1;     // different from merge-sort
                }
        }

        while( l1 <= r1 )
                B[--n] = A[r1--];

        while( l2 <= r2 )
                B[--n] = A[r2--];

        while( n <= r - p )     {       // copy back
                A[p+n] = B[n];
                n++;
        }

        free(B);
        return cnt;
}
