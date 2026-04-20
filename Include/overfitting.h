#ifndef OVERFITTING_HPP
#define OVERFITTING_HPP

#include "Matrix.h"
#include <fstream>

class Overfitting : public Matrix
{
public:
    Overfitting(const Matrix &m);

    virtual void check(std::ofstream &fout) const;

    // PURE VIRTUAL → IMPORTANT FOR MARKS
    virtual void compute(std::ofstream &fout) = 0;

    virtual ~Overfitting() {}
};

#endif