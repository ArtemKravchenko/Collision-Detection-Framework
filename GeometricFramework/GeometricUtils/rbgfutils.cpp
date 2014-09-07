#include "rbgfutils.h"
#include "rbmfutils.h"

// Determinant Predicates
RBGFOrientated2DType RBGFUtils::orientated2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3)
{
    if(p1->getDimention() != 2 || p2->getDimention() != 2 || p3->getDimention() != 2)
        return RBGFOrientated2DError;

    double p1Els[] = p1->getCoordinates();
    double p2Els[] = p2->getCoordinates();
    double p3Els[] = p3->getCoordinates();
    RBMFUtils *utils = RBMFUtils.sharedUtils();
    double elements[9] = {p1Els[0], p1Els[1], 1,
                          p2Els[0], p2Els[1], 1,
                          p3Els[0], p3Els[1], 1};
    double det = utils->determinantOfThreeDimention(elements);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFOrientated2DCounterClockwise;
        else if(det < 0)
            return RBGFOrientated2DClockwise;
        else if(det == 0)
            return RBGFOrientated2DCollinear;
    }
    else
    {
        return RBGFOrientated2DError;
    }

}
RBGFOrientated3DType RBGFUtils::orientated3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4)
{
    if(p1->getDimention() != 3 || p2->getDimention() != 3 || p3->getDimention() != 3 || p4->getDimention() != 3)
        return RBGFOrientated3DError;

    double p1Els[] = p1->getCoordinates();
    double p2Els[] = p2->getCoordinates();
    double p3Els[] = p3->getCoordinates();
    double p4Els[] = p4->getCoordinates();
    RBMFUtils *utils = RBMFUtils::sharedUtils();
    double elements[16] = {p1Els[0], p1Els[1], p1Els[2], 1,
                          p2Els[0], p2Els[1], p2Els[2], 1,
                          p3Els[0], p3Els[1], p3Els[2], 1,
                          p4Els[0], p4Els[1], p4Els[2], 1};
    double det = utils->determinant(elements, 16, 4);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFOrientated3DCounterClockwise;
        else if(det < 0)
            return RBGFOrientated3DClockwise;
        else if(det == 0)
            return RBGFOrientated3DComplanar;
    }
    else
    {
        return RBGFOrientated3DError;
    }
}
RBGFInCircle2DType RBGFUtils::inCircle2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4)
{
    if(p1->getDimention() != 2 || p2->getDimention() != 2 || p3->getDimention() != 2 || p4->getDimention() != 2)
        return RBGFInCircle2DError;

    double p1Els[] = p1->getCoordinates();
    double p2Els[] = p2->getCoordinates();
    double p3Els[] = p3->getCoordinates();
    double p4Els[] = p4->getCoordinates();
    RBMFUtils *utils = RBMFUtils::sharedUtils();
    double elements[16] = {p1Els[0], p1Els[1], p1Els[0]*p1Els[0] + p1Els[1]*p1Els[1], 1,
                          p2Els[0], p2Els[1], p2Els[0]*p2Els[0] + p2Els[1]*p2Els[1], 1,
                          p3Els[0], p3Els[1], p3Els[0]*p3Els[0] + p3Els[1]*p3Els[1], 1,
                          p4Els[0], p4Els[1], p4Els[0]*p4Els[0] + p4Els[1]*p4Els[1], 1};

    double det = utils->determinant(elements, 16, 4);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFInCircle2DIndside;
        else if(det < 0)
            return RBGFInCircle2DOutside;
        else if(det == 0)
            return RBGFInCircle2DCocircular;
    }
    else
    {
        return RBGFInCircle2DError;
    }
}
RBGFInSphere3DType RBGFUtils::inSphere3D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3, RBGFPoint *p4, RBGFPoint *p5)
{
    if(p1->getDimention() != 3 || p2->getDimention() != 3 || p3->getDimention() != 3 || p4->getDimention() != 3 || p5->getDimention() != 3)
        return RBGFInSphere3DError;

    double p1Els[] = p1->getCoordinates();
    double p2Els[] = p2->getCoordinates();
    double p3Els[] = p3->getCoordinates();
    double p4Els[] = p4->getCoordinates();
    double p5Els[] = p5->getCoordinates();
    RBMFUtils *utils = RBMFUtils::sharedUtils();
    double elements[25] = {p1Els[0], p1Els[1], p1Els[2], p1Els[0]*p1Els[0] + p1Els[1]*p1Els[1] + p1Els[2]*p1Els[2], 1,
                          p2Els[0], p2Els[1], p2Els[2], p2Els[0]*p2Els[0] + p2Els[1]*p2Els[1] + p2Els[2]*p2Els[2], 1,
                          p3Els[0], p3Els[1], p3Els[2], p3Els[0]*p3Els[0] + p3Els[1]*p3Els[1] + p3Els[2]*p3Els[2], 1,
                          p4Els[0], p4Els[1], p4Els[2], p4Els[0]*p4Els[0] + p4Els[1]*p4Els[1] + p4Els[2]*p4Els[2], 1};

    double det = utils->determinant(elements, 25, 5);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFInSphere3DIndside;
        else if(det < 0)
            return RBGFInSphere3DOutside;
        else if(det == 0)
            return RBGFInSphere3DCospherial;
    }
    else
    {
        return RBGFInSphere3DError;
    }
}
