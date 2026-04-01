

#ifndef JACOBI_H
#define JACOBI_H

#include "Iterative.h"
#include <fstream>


class Jacobi : public Iterative
{
public:
    Jacobi(const Matrix &m);
    bool isDiagonallyDominant();  
    void solve(std::ofstream &fout) override;
    void setTolerance(double tolerance) { tol = tolerance; }
};

#endif