#ifndef CURVEFITTING_HPP
#define CURVEFITTING_HPP
#include "Matrix.h"
#include <fstream>

class CurveFitting : public Matrix
{
public:
    
    CurveFitting(const Matrix &m);
    void check(std::ofstream &fout) const;
    virtual void compute(std::ofstream &fout, int degree) = 0;
    virtual ~CurveFitting() {}
};

#endif