#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Matrix.h"

class LinearSystem : public Matrix
{
protected:
    int n;

public:
    LinearSystem(const Matrix &m);
    virtual void solve(ofstream &fout)=0;
};

#endif