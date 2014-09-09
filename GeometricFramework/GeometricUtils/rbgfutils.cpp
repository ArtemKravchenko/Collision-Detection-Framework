#include "rbgfutils.h"
#include "rbmfutils.h"
#include "rbgfvector.h"
#include <array>
#include <float.h>
#include <math.h>
#include <stdlib.h>

// Determinant Predicates
RBGFOrientated2DType RBGFUtils::orientated2D(RBGFPoint *p1, RBGFPoint *p2, RBGFPoint *p3)
{
    if(p1->getDimention() != 2 || p2->getDimention() != 2 || p3->getDimention() != 2)
        return RBGFOrientated2DError;

    const double *p1Els = p1->getCoordinates();
    const double *p2Els = p2->getCoordinates();
    const double *p3Els = p3->getCoordinates();
    RBMFUtils utils = RBMFUtils::sharedUtils();
    std::array<double, 9> elements = {p1Els[0], p1Els[1], 1,
                          p2Els[0], p2Els[1], 1,
                          p3Els[0], p3Els[1], 1};
    double det = utils.determinantOfThreeDimention(elements);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFOrientated2DCounterClockwise;
        else if(det < 0)
            return RBGFOrientated2DClockwise;
        else
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

    const double *p1Els = p1->getCoordinates();
    const double *p2Els = p2->getCoordinates();
    const double *p3Els = p3->getCoordinates();
    const double *p4Els = p4->getCoordinates();
    RBMFUtils utils = RBMFUtils::sharedUtils();
    double elements[16] = {p1Els[0], p1Els[1], p1Els[2], 1,
                          p2Els[0], p2Els[1], p2Els[2], 1,
                          p3Els[0], p3Els[1], p3Els[2], 1,
                          p4Els[0], p4Els[1], p4Els[2], 1};
    double det = utils.determinant(elements, 16, 4);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFOrientated3DCounterClockwise;
        else if(det < 0)
            return RBGFOrientated3DClockwise;
        else
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

    const double *p1Els = p1->getCoordinates();
    const double *p2Els = p2->getCoordinates();
    const double *p3Els = p3->getCoordinates();
    const double *p4Els = p4->getCoordinates();
    RBMFUtils utils = RBMFUtils::sharedUtils();
    double elements[16] = {p1Els[0], p1Els[1], p1Els[0]*p1Els[0] + p1Els[1]*p1Els[1], 1,
                          p2Els[0], p2Els[1], p2Els[0]*p2Els[0] + p2Els[1]*p2Els[1], 1,
                          p3Els[0], p3Els[1], p3Els[0]*p3Els[0] + p3Els[1]*p3Els[1], 1,
                          p4Els[0], p4Els[1], p4Els[0]*p4Els[0] + p4Els[1]*p4Els[1], 1};

    double det = utils.determinant(elements, 16, 4);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFInCircle2DIndside;
        else if(det < 0)
            return RBGFInCircle2DOutside;
        else
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

    const double *p1Els = p1->getCoordinates();
    const double *p2Els = p2->getCoordinates();
    const double *p3Els = p3->getCoordinates();
    const double *p4Els = p4->getCoordinates();
    const double *p5Els = p5->getCoordinates();
    RBMFUtils utils = RBMFUtils::sharedUtils();
    double elements[25] = {p1Els[0], p1Els[1], p1Els[2], p1Els[0]*p1Els[0] + p1Els[1]*p1Els[1] + p1Els[2]*p1Els[2], 1,
                          p2Els[0], p2Els[1], p2Els[2], p2Els[0]*p2Els[0] + p2Els[1]*p2Els[1] + p2Els[2]*p2Els[2], 1,
                          p3Els[0], p3Els[1], p3Els[2], p3Els[0]*p3Els[0] + p3Els[1]*p3Els[1] + p3Els[2]*p3Els[2], 1,
                          p4Els[0], p4Els[1], p4Els[2], p4Els[0]*p4Els[0] + p4Els[1]*p4Els[1] + p4Els[2]*p4Els[2], 1,
                          p5Els[0], p5Els[1], p5Els[2], p5Els[0]*p5Els[0] + p5Els[1]*p5Els[1] + p5Els[2]*p5Els[2], 1};

    double det = utils.determinant(elements, 25, 5);
    if(det != -DBL_MAX)
    {
        if(det > 0)
            return RBGFInSphere3DIndside;
        else if(det < 0)
            return RBGFInSphere3DOutside;
        else
            return RBGFInSphere3DCospherial;
    }
    else
    {
        return RBGFInSphere3DError;
    }
}
void RBGFUtils::barycentric(RBGFPoint* const a,RBGFPoint* const b, RBGFPoint* const c, RBGFPoint* const p, float &u, float &v, float &w)
{
    RBGFVector *v0 = new RBGFVector(a, b), *v1 = new RBGFVector(a, c), *v2 = new RBGFVector(p, a);
    float d00 = v0->dotProduct(v0);
    float d01 = v0->dotProduct(v1);
    float d11 = v1->dotProduct(v1);
    float d20 = v2->dotProduct(v0);
    float d21 = v2->dotProduct(v1);
    float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
    delete v0;
    delete v1;
    delete v2;
}
void RBGFUtils::barycentricWith2DProjection(RBGFPoint* const a, RBGFPoint* const b, RBGFPoint* const c, RBGFPoint* const p, float &u, float &v, float &w)
{
    // Unnormalized triangle normal
    RBGFVector *v0 = new RBGFVector(a, b), *v1 = new RBGFVector(a, c);
    RBGFVector &m = v0->crossProduct(*v1);
    // Nominators and one-over-denominator for u and v ratios
    float nu, nv, odd;
    // Absolute components for determining projection plane
    const double *els = (m.getEnd() - m.getStart()).getCoordinates();
    float x = abs(els[0]), y = abs(els[1]), z = abs(els[2]);
    // Compute areas in plane of largest projection
    const double *pEls = p->getCoordinates();
    const double *cEls = c->getCoordinates();
    const double *bEls = b->getCoordinates();
    const double *aEls = a->getCoordinates();
    if (x >= y && x >= z) {
        nu = triArea2D(pEls[1], pEls[2], bEls[1], bEls[2], cEls[1], cEls[2]);
        nv = triArea2D(pEls[1], pEls[2], cEls[1], cEls[2], aEls[1], aEls[2]);
        odd = 1.0f / (((m.getEnd() - m.getStart()).getCoordinates())[0]);
    } else if (y >= x && y >= z) {
        nu = triArea2D(pEls[0], pEls[2], bEls[0], bEls[2], cEls[0], cEls[2]);
        nv = triArea2D(pEls[0], pEls[2], cEls[0], cEls[2], aEls[0], aEls[2]);
        odd = 1.0f / -(((m.getEnd() - m.getStart()).getCoordinates())[1]);
    } else {
        nu = triArea2D(pEls[0], pEls[1], bEls[0], bEls[1], cEls[0], cEls[1]);
        nv = triArea2D(pEls[0], pEls[1], cEls[0], cEls[1], aEls[0], aEls[1]);
        odd = 1.0f / (((m.getEnd() - m.getStart()).getCoordinates())[2]);
    }
    u = nu * odd;
    v = nv * odd;
    w = 1.0f - u - w;
    delete v0;
    delete v1;
}

int RBGFUtils::pointInTriangle(RBGFPoint* const a, RBGFPoint* const b, RBGFPoint* const c, RBGFPoint* const p)
{
    float u, v, w;
    barycentricWith2DProjection(a, b, c, p, u, v, w);
    return  v >= 0.0f && w >= 0.0f && (v + w) <= 1.0f;
}
// TEST AXIS-ALIGNED BOUNDING BOXES
int RBGFUtils::testAABBAABB(RBGFAxisAlignedBoundingBox * const a, RBGFAxisAlignedBoundingBox * const b)
{
    if (a->getDimension() == b->getDimension())
        return -1;
    
    const double *aDis = a->getDistances();
    const double *bDis = b->getDistances();
    const RBGFPoint* aCtr = a->getCenter();
    const RBGFPoint* bCtr = b->getCenter();
    const double *aCtrEls = aCtr->getCoordinates();
    const double *bCtrEls = bCtr->getCoordinates();
    if (abs(aCtrEls[0] - bCtrEls[0]) > (aDis[0] + bDis[0])) return 0;
    if (abs(aCtrEls[1] - bCtrEls[1]) > (aDis[1] + bDis[1])) return 0;
    if (a->getDimension() == 3)
        if (abs(aCtrEls[2] - bCtrEls[2]) > (aDis[2] + bDis[2])) return 0;
    return 1;
}
void RBGFUtils::extremePointsAlongDirection(RBGFVector* const dir, RBGFPoint* const pt[], int n, int *imin, int *imax)
{
    double minproj = DBL_MAX, maxproj = -DBL_MAX;
    for (int i = 0; i < n; i++) {
        // Project vector from origin to point onto direction vector
        double proj = dir->dotProduct(pt[i]);
        // Keep track of least distant point along direction vector
        if (proj < minproj) {
            minproj = proj;
            *imin = i;
        }
        // Keep track of most distant point along direction vector
        if (proj > maxproj) {
            maxproj = proj;
            *imax = i;
        }
    }
}
// TEST SPHERE
int RBGFUtils::TestSphereSphere(RBGFSphere * const a, RBGFSphere * const b)
{
    // Calculate squared distance between centers
    const RBGFPoint *aCtr = a->getCenter();
    const RBGFPoint *bCtr = b->getCenter();
    if (aCtr->getDimention() != bCtr->getDimention()) {
        return -1;
    }
    RBGFPoint *vPoint;
    const double* aCtrEls = aCtr->getCoordinates();
    const double* bCtrEls = bCtr->getCoordinates();
    if (aCtr->getDimention() == 2) {
        vPoint = new RBGFPoint(aCtrEls[0] - bCtrEls[0], aCtrEls[1] - bCtrEls[1]);
    } else {
        vPoint = new RBGFPoint(aCtrEls[0] - bCtrEls[0], aCtrEls[1] - bCtrEls[1], aCtrEls[2] - bCtrEls[2]);
    }
    RBGFVector *d = new RBGFVector(vPoint);
    double dist2 = d->dotProduct(d);
    // Spheres intersect if squared distance is less than squared sum of radii float radiusSum = a.r + b.r;
    double radiusSum = a->getRadius() + b->getRadius();
    delete vPoint;
    delete d;
    return dist2 <= radiusSum * radiusSum;
}
void RBGFUtils::MostSeparatedPointsOnAABB(int &min, int &max, RBGFPoint * const pt[], int numPts)
{
    int dim = (pt[0])->getDimention();
    // First find most extreme points along principal axes
    int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
    for (int i = 1; i < numPts; i++) {
        const double *els = pt[i]->getCoordinates();
        const double *minXEls = pt[minx]->getCoordinates();
        const double *maxXEls = pt[maxx]->getCoordinates();
        const double *minYEls = pt[miny]->getCoordinates();
        const double *maxYEls = pt[maxy]->getCoordinates();
        if (els[0] < minXEls[0]) minx = i;
        if (els[0] > maxXEls[0]) maxx = i;
        if (els[1] < minYEls[1]) miny = i;
        if (els[1] > maxYEls[1]) maxy = i;
        if (dim == 3) {
            const double *minZEls = pt[minz]->getCoordinates();
            const double *maxZEls = pt[maxz]->getCoordinates();
            if (els[2] < minZEls[2]) minz = i;
            if (els[2] > maxZEls[2]) maxz = i;
        }
    }
}
void RBGFUtils::SphereFromDistantPoints(RBGFSphere &s, RBGFPoint * const pt[], int numPts)
{
    // Find the most separated point pair defining the encompassing AABB
    int min, max;
    MostSeparatedPointsOnAABB(min, max, pt, numPts);
    // Set up sphere to just encompass these two points
    RBGFPoint newCenter = *(pt[min]) + *(pt[max]);
    newCenter = *newCenter.productByNumber(0.5f);
    s.setCenter(&newCenter);
    delete &newCenter;
    RBGFPoint endPoint1 = (*(pt[max]) - *s.getCenter());
    RBGFVector *v1 = new RBGFVector(&endPoint1);
    double newRadius = v1->dotProduct(v1);
    s.setRadius(sqrt(newRadius));
    delete &endPoint1;
    delete v1;
}
// Given Sphere s and Point p, update s (if needed) to just encompass p
void RBGFUtils::SphereOfSphereAndPt(RBGFSphere& s, RBGFPoint const *p)
{
    // Compute squared distance between point and sphere center
    const RBGFPoint *startPoint = s.getCenter();
    RBGFVector *d = new RBGFVector(startPoint, p);
    double dist2 = d->dotProduct(d);
    // Only update s if point p is outside it
    double sphereRadius = s.getRadius();
    if (dist2 > sphereRadius * sphereRadius) {
        double dist = sqrt(dist2);
        double newRadius = (sphereRadius + dist) * 0.5f;
        double k = (newRadius - sphereRadius) / dist;
        s.setRadius(newRadius);
        RBGFPoint &p1 = const_cast<RBGFPoint&>(*p);
        RBGFPoint newCenter = p1 - *startPoint;
        newCenter = *newCenter.productByNumber(k);
        newCenter = newCenter + *s.getCenter();
        s.setCenter(&newCenter);
        delete &newCenter;
    }
}
// The full code for computing the approximate bounding sphere becomes
void RBGFUtils::RitterSphere(RBGFSphere &s, RBGFPoint * const pt[], int numPts)
{
    // Get sphere encompassing two approximately most distant points
    SphereFromDistantPoints(s, pt, numPts);
    // Grow sphere to include all points
    for (int i = 0; i < numPts; i++)
        SphereOfSphereAndPt(s, pt[i]);
}
// Private functions
inline float RBGFUtils::triArea2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
    return (x1-x2)*(y2-y3)-(x2-x3)*(y1-y2);
}

