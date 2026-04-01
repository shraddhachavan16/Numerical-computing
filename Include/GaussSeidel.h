#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H


#include "Iterative.h"
#include <fstream>

class GaussSeidel : public Iterative
{
public:
    GaussSeidel(const Matrix &m);
    bool isDiagonallyDominant();
    void solve(std::ofstream &fout) override;
    void setTolerance(double tolerance) { tol = tolerance; }
};

#endif