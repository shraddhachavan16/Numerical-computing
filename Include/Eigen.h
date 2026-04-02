#ifndef EIGEN_H
#define EIGEN_H

#include "Matrix.h"

class Eigen : public Matrix
{
protected:
    int n;

public:
    Eigen(const Matrix &m);
};

#endif

