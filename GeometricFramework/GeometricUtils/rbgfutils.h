#ifndef RBGFUTILS_H
#define RBGFUTILS_H
#include "rbgfpoint.h"

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
public:
    // Determinant Predicates
    RBGFOrientated2DType orientated2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3);
    RBGFOrientated3DType orientated3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4);
    RBGFInCircle2DType inCircle2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4);
    RBGFInSphere3DType inSphere3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4, RBGFPoint *p5);
    // Singleton
    static RBGFUtils& sharedUtils()
    {
        static RBGFUtils utils;
        return utils;
    }
    RBGFUtils() {}
    RBGFUtils(RBMFUtils const&);              // Don't Implement.
    void operator=(RBGFUtils const&);         // Don't Implement.
};

#endif // RBGFUTILS_H
