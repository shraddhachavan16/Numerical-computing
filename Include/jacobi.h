#ifndef JACOBI_H
#define JACOBI_H

#include "Iterative.h"
#include <vector>   // ✅ needed

class Jacobi : public Iterative
{
public:
    Jacobi(const Matrix &m); 

    std::vector<double> solve() override;   // ✅ FIXED
};

#endif