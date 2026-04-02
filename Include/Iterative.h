// #ifndef ITERATIVE_H
// #define ITERATIVE_H

// #include "LinearSystem.h"
// #include <fstream>

// class Iterative : public LinearSystem
// {
// protected:
//     int maxIter;
//     double tol;

// public:
//     Iterative(const Matrix &m, int maxIter = 500, double tol = 1e-6);

//     bool isDiagonallyDominant();

//     virtual void solve(std::ofstream &fout) = 0; // pure virtual
// };

// #endif

#ifndef ITERATIVE_H
#define ITERATIVE_H

#include "LinearSystem.h"

class Iterative : public LinearSystem
{
protected:
    int maxIter;
    double tol;

public:
    Iterative(const Matrix &m);
    bool isDiagonallyDominant();
    bool makeDiagonallyDominant();
    virtual std::vector<double> solve() = 0;

};

#endif