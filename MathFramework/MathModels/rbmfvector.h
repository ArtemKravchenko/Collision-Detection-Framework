#ifndef RBMFVECTOR_H
#define RBMFVECTOR_H

class RBMFVector
{
public:
    RBMFVector();
    RBMFVector(int dimention, const double* elements);
    ~RBMFVector();
    double getElements() const;
    int getDimention() const;
private:
    int _dimention;
    double* _elements;
};

#endif // RBMFVECTOR_H
