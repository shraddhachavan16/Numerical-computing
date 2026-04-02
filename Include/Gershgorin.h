#ifndef GERSHGORIN_H
#define GERSHGORIN_H

#include "Eigen.h"
#include <fstream>

class Gershgorin : public Eigen
{
public:
    Gershgorin(const Matrix &m);
    void gershgorinTheorem(std::ofstream &fout);
};

#endif