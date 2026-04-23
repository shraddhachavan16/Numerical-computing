#ifndef LEASTSQUARES_HPP
#define LEASTSQUARES_HPP

#include "CurveFitting.h"
#include <fstream>

class LeastSquares : public CurveFitting
{
public:
    LeastSquares(const Matrix &m);
    void compute(std::ofstream &fout, int degree) override;
};

#endif