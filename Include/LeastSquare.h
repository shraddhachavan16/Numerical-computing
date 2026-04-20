#ifndef LEASTSQUARES_HPP
#define LEASTSQUARES_HPP

#include "overfitting.h"

class LeastSquares : public Overfitting
{
public:
    LeastSquares(const Matrix &m);
    void compute(std::ofstream &fout) override;
};

#endif