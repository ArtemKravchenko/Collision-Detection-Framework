#ifndef RBMFVECTOR_H
#define RBMFVECTOR_H

class RBMFVector
{
public:
    RBMFVector();
    RBMFVector(int dimention, const double elements[]);
    ~RBMFVector();
    const double *getElements() const;
    int getDimention();
    double dotProduct(RBMFVector *rhs);
protected:
    int _dimention;
    double* _elements;
};

#endif // RBMFVECTOR_H
