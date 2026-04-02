

#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H

#include "Iterative.h"
#include <vector>   // ✅ ADD THIS

class GaussSeidel : public Iterative
{
public:
    GaussSeidel(const Matrix &m);

    std::vector<double> solve() override;   // ✅ ADD THIS
};

#endif