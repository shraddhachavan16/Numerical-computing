#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Matrix.h"
#include <vector>
#include <fstream>

using namespace std;

class Interpolation : public Matrix
{
public:
    Interpolation(const Matrix &m);
    virtual double interpolate(double value) = 0;
    virtual void displayData(ofstream &fout) const;
    virtual ~Interpolation() {}
};

#endif