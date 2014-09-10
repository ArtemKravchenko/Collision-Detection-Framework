#ifndef RBGFUTILS_H
#define RBGFUTILS_H
#include "rbgfpoint.h"
#include "rbgfaxisalignedboundingbox.h"
#include "rbgfsphere.h"
#include "rbmfmatrix.h"

enum RBGFOrientated2DType {
    RBGFOrientated2DCounterClockwise,   // Lies to the left of the directed line
    RBGFOrientated2DClockwise,          // Lies to the right of the directed line
    RBGFOrientated2DCollinear,
    RBGFOrientated2DError
};

enum RBGFOrientated3DType {
    RBGFOrientated3DCounterClockwise,   // Lies above of the directed plane
    RBGFOrientated3DClockwise,          // Lies below of the directed plane
    RBGFOrientated3DComplanar,
    RBGFOrientated3DError
};

enum RBGFInCircle2DType {
    RBGFInCircle2DIndside,
    RBGFInCircle2DOutside,
    RBGFInCircle2DCocircular,
    RBGFInCircle2DError
};

enum RBGFInSphere3DType {
    RBGFInSphere3DIndside,
    RBGFInSphere3DOutside,
    RBGFInSphere3DCospherial,
    RBGFInSphere3DError
};


class RBGFUtils
{
private:
    inline float triArea2D(float x1, float y1, float x2, float y2, float x3, float y3);
    // Compute variance of a set of 1D values
    double variance(double x[], int n);
    void CovarianceMatrix(RBMFMatrix &cov, RBGFPoint * const pt[], int numPts);
    // 2-by-2 Symmetric Schur decomposition. Given an n-by-n symmetric matrix
    // and indices p, q such that 1 <= p < q <= n, computes a sine-cosine pair
    // (s, c) that will serve to form a Jacobi rotation matrix.
    //
    // See Golub, Van Loan, Matrix Computations, 3rd ed, p428
    void SymSchur2(RBMFMatrix &a, int p, int q, double &c, double &s) ;
public:
    // Determinant Predicates
    RBGFOrientated2DType orientated2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3);
    RBGFOrientated3DType orientated3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4);
    RBGFInCircle2DType inCircle2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4);
    RBGFInSphere3DType inSphere3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4, RBGFPoint *p5);
    void barycentric(RBGFPoint* a, RBGFPoint* b, RBGFPoint* c, RBGFPoint* p, float &u, float &v, float &w);
    void barycentricWith2DProjection(RBGFPoint* a, RBGFPoint* b, RBGFPoint* c, RBGFPoint* p, float &u, float &v, float &w);
    int pointInTriangle(RBGFPoint* const a, RBGFPoint* const b, RBGFPoint* const c, RBGFPoint* const p);
    // TEST AXIS-ALIGNED BOUNDING BOXES
    int testAABBAABB(RBGFAxisAlignedBoundingBox * const a, RBGFAxisAlignedBoundingBox * const b);
    void extremePointsAlongDirection(RBGFVector * const dir, RBGFPoint* const pt[], int n, int *imin, int *imax); // Returns indices imin and imax into pt[] array of the least and most, respectively, distant points along the direction dir
    // TEST SPHERE
    int TestSphereSphere(RBGFSphere * const a, RBGFSphere * const b);
    // Compute indices to the two most separated points of the (up to) six points // defining the AABB encompassing the point set. Return these as min and max.
    void MostSeparatedPointsOnAABB(int &min, int &max, RBGFPoint * const pt[], int numPts);
    void SphereFromDistantPoints(RBGFSphere &s, RBGFPoint * const pt[], int numPts);
    // Given Sphere s and Point p, update s (if needed) to just encompass p
    void SphereOfSphereAndPt(RBGFSphere &s, RBGFPoint const *p);
    // The full code for computing the approximate bounding sphere becomes
    void RitterSphere(RBGFSphere &s, RBGFPoint * const pt[], int numPts);
    // Singleton
    static RBGFUtils& sharedUtils()
    {
        static RBGFUtils utils;
        return utils;
    }
    RBGFUtils() {}
    RBGFUtils(RBGFUtils const&);              // Don't Implement.
    void operator=(RBGFUtils const&);         // Don't Implement.
};

#endif // RBGFUTILS_H
