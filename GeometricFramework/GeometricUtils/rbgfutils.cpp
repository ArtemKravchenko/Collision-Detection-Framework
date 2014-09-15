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
int RBGFUtils::testSphereSphere(RBGFSphere * const a, RBGFSphere * const b)
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
void RBGFUtils::mostSeparatedPointsOnAABB(int &min, int &max, RBGFPoint * const pt[], int numPts)
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
void RBGFUtils::sphereFromDistantPoints(RBGFSphere &s, RBGFPoint * const pt[], int numPts)
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
void RBGFUtils::sphereOfSphereAndPt(RBGFSphere& s, RBGFPoint const *p)
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
    delete d;
}
// The full code for computing the approximate bounding sphere becomes
void RBGFUtils::ritterSphere(RBGFSphere &s, RBGFPoint * const pt[], int numPts)
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
double RBGFUtils::variance(double x[], int n)
{
    double u=0.0f;
    for (int i = 0; i < n; i++) u += x[i];
    u /= n;
    double s2 = 0.0f;
    for (int i = 0; i < n; i++) s2 += (x[i] - u) * (x[i] - u);
    return s2 / n;
}
void RBGFUtils::covarianceMatrix(RBMFMatrix &cov, RBGFPoint * const pt[], int numPts)
{
    double oon = 1.0f / (double)numPts;
    RBGFPoint *c = new RBGFPoint(0, 0, 0);
    double e00, e11, e22, e01, e02, e12;
    // Compute the center of mass (centroid) of the points
    for (int i = 0; i < numPts; i++)
        c = c + pt[i];
    c = c->productByNumber(oon);
    // Compute covariance elements
    e00 = e11 = e22 = e01 = e02 = e12 = 0;
    for (int i = 0; i < numPts; i++)
    {
        // Translate points so center of mass is at origin
        RBGFPoint p = *(pt[i]) - *c;
        // Compute covariance of translated points
        const double *els = p.getCoordinates();
        e00 += els[0] * els[0];
        e11 += els[1] * els[1];
        e22 += els[2] * els[2];
        e01 += els[0] * els[1];
        e02 += els[0] * els[2];
        e12 += els[1] * els[2];
    }
    // Fill in the covariance matrix elements
    cov.setElementAtInxex(e00 * oon, 0);
    cov.setElementAtInxex(e11 * oon, 4);
    cov.setElementAtInxex(e22 * oon, 8);
    cov.setElementAtInxex(e01 * oon, 1);
    cov.setElementAtInxex(e01 * oon, 3);
    cov.setElementAtInxex(e02 * oon, 2);
    cov.setElementAtInxex(e02 * oon, 6);
    cov.setElementAtInxex(e12 * oon, 5);
    cov.setElementAtInxex(e12 * oon, 7);
    delete c;
}
void RBGFUtils::symSchur2(RBMFMatrix &a, int p, int q, double &c, double &s)
{
    const double *els = a.getElements();
    double num = els[p*3 + q];
    if (abs(num) > 0.0001)
    {
        double n1 = els[q*3 + q];
        double n2 = els[p*3 + p];
        double n3 = els[p*3 + q];
        double r=(n1 - n2)/(2.0 * n3);
        double t;
        if (r >= 0.0) t = 1.0 / (r + sqrt(1.0 + r*r));
        else t = -1.0 / (-r + sqrt(1.0 + r*r));
        c = 1.0 / sqrt(1.0 + t*t); s = t * c;
    }
    else
    {
        c = 1.0; s = 0.0;
    }
}
void RBGFUtils::eigenSphere(RBGFSphere &eigSphere, RBGFPoint * const pt[], int numPts)
{
    double *els = new double {0, 0, 0, 0, 0, 0, 0, 0, 0};
    RBMFMatrix *m = new RBMFMatrix(3, 3, els), *v = new RBMFMatrix(3, 3, els);
    // Compute the covariance matrix m
    covarianceMatrix(*m, pt, numPts);
    // Decompose it into eigenvectors (in v) and eigenvalues (in m)
    jacobi(*m, *v);
    // Find the component with largest magnitude eigenvalue (largest spread)
    const RBGFPoint *tmp = new RBGFPoint(0,0,0);
    RBGFVector *e = new RBGFVector(tmp);
    int maxc = 0;
    float maxf, maxe = abs(m[0][0]);
    if ((maxf = abs(m[1][1])) > maxe) maxc = 1, maxe = maxf;
    if ((maxf = Abs(m[2][2])) > maxe) maxc = 2, maxe = maxf;
    e[0] = v[0][maxc]; e[1] = v[1][maxc]; e[2] = v[2][maxc];
    // Find the most extreme points along direction ’e’
    int imin, imax;
    extremePointsAlongDirection(e, pt, numPts, &imin, &imax);
    RBGFPoint * const minpt = pt[imin];
    RBGFPoint * const maxpt = pt[imax];
    RBGFPoint * dotPoint = maxpt - minpt;
    RBGFVector *dotVector = new RBGFVector(dotPoint);
    double dist = sqrt(dotVector->dotProduct(dotVector));
    eigSphere.setRadius(dist * 0.5);
    eigSphere.setCenter((minpt + maxpt)->productByNumber(0.5));
    delete m;
    delete tmp;
    delete e;
    delete dotVector;
}
void RBGFUtils::ritterEigenSphere(RBGFSphere &s, RBGFPoint * const pt[], int numPts)
{
    // Start with sphere from maximum spread
    eigenSphere(s, pt, numPts);
    // Grow sphere to include all points
    for (int i = 0; i < numPts; i++)
        sphereOfSphereAndPt(s, pt[i]);
}
void RBGFUtils::ritterIterative(RBGFSphere &s, RBGFPoint const * pt[], int numPts)
{
    const int NUM_ITER = 8;
    ritterSphere(s, pt, numPts);
    RBGFSphere s2 = s; for (int k = 0; k < NUM_ITER; k++) {
        // Shrink sphere somewhat to make it an underestimate (not bound)
        s2.setRadius = s2.getRadius() * 0.95;
        // Make sphere bound data again
        for (int i = 0; i < numPts; i++) {
            // Swap pt[i] with pt[j], where j randomly from interval [i+1,numPts-1]
            doRandomSwap();
            sphereOfSphereAndPt(s2, pt[i]);
        }
        // Update s whenever a tighter sphere is found
        if (s2.getRadius() < s.getRadius())
            s = s2;
    }
}
RBGFSphere RBGFUtils::welzlSphere(RBGFPoint const * pt[], unsigned int numPts, RBGFPoint const * sos[], unsigned int numSos)
{
    // if no input points, the recursion has bottomed out. Now compute an
    // exact sphere based on points in set of support (zero through four points)
    if (numPts == 0)
    {
        switch (numSos)
        {
            case 0:
                return RBGFSphere();
            case 1:
                return RBGFSphere(sos[0]);
            case 2:
                return RBGFSphere(sos[0], sos[1]);
            case 3:
                return RBGFSphere(sos[0], sos[1], sos[2]);
            case 4:
                return RBGFSphere(sos[0], sos[1], sos[2], sos[3]);
        }
    }
    // Pick a point at "random" (here just the last point of the input set)
    int index = numPts - 1;
    // Recursively compute the smallest bounding sphere of the remaining points
    RBGFSphere smallestSphere = welzlSphere(pt, numPts - 1, sos, numSos);
    // (*) // If the selected point lies inside this sphere, it is indeed the smallest
    if(pointInsideSphere(pt[index], smallestSphere))
        return smallestSphere;
    // Otherwise, update set of support to additionally contain the new point
    sos[numSos] = pt[index];
    // Recursively compute the smallest sphere of remaining points with new s.o.s.
    return welzlSphere(pt, numPts - 1, sos, numSos + 1);
}
int RBGFUtils::testOBBOBB(RBGFOrientatedBoundingBox &a, RBGFOrientatedBoundingBox &b)
{
    double ra, rb;
    , AbsR;
    double *els = new double[9];
    RBGFVector *au[] = a.getLocalAxis();
    RBGFVector *bu[] = b.getLocalAxis();
    // Compute rotation matrix expressing b in a’s coordinate frame
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            els[i*3 + j] = au[i]->dotProduct(bu[j]);
    RBMFMatrix *R = new RBMFMatrix(3, 3, els);
    // Compute translation vector t
    RBGFVector t = b.c-a.c;
    // Bring translation into a’s coordinate frame
    t = Vector(Dot(t, a.u[0]), Dot(t, a.u[2]), Dot(t, a.u[2]));
    // Compute common subexpressions. Add in an epsilon term to
    // counteract arithmetic errors when two edges are parallel and
    // their cross product is (near) null (see text for details)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            AbsR[i][j] = Abs(R[i][j]) + 0.0001; // EPSILON
    // Test axes L = A0, L = A1, L = A2 for (int i = 0; i < 3; i++) { ra = a.e[i]; rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2]; if (Abs(t[i]) > ra + rb) return 0; }
    // Test axes L = B0, L = B1, L = B2 for (int i = 0; i < 3; i++) { ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i]; rb = b.e[i]; if (Abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0; }
    // Test axis L = A0 x B0 ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0]; rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1]; if (Abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;
    // Test axis L = A0 x B1 ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1]; rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0]; if (Abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;
    // Test axis L = A0 x B2 ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2]; rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0]; if (Abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;
    // Test axis L = A1 x B0 ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0]; rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
    if (Abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;
    // Test axis L = A1 x B1 ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1]; rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0]; if (Abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;
    // Test axis L = A1 x B2 ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2]; rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0]; if (Abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;
    // Test axis L = A2 x B0 ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0]; rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1]; if (Abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;
    // Test axis L = A2 x B1 ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1]; rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0]; if (Abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;
    // Test axis L = A2 x B2 ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2]; rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0]; if (Abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;
    // Since no separating axis is found, the OBBs must be intersecting return 1;
}
