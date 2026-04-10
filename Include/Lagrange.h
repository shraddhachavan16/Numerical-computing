#ifndef LAGRANGE_H
#define LAGRANGE_H

#include "Interpolation.h"
#include <fstream>

using namespace std;

class Lagrange : public Interpolation
{
public:
    Lagrange(const Matrix &m);

    double interpolate(double value) override;

    void printPolynomial(ofstream &fout); // optional
};

#endif