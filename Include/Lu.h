#ifndef LUDECOMPOSITION_HPP
#define LUDECOMPOSITION_HPP

#include "Linearsystem.h"

class LUDoolittle : public LinearSystem
{
public:
    LUDoolittle(const Matrix &m);
    void solve(ofstream &fout);
};

class LUCrout : public LinearSystem
{
public:
    LUCrout(const Matrix &m);
    void solve(ofstream &fout);
};

class LUCholesky : public LinearSystem
{
public:
    LUCholesky(const Matrix &m);
    void solve(ofstream &fout);
};

#endif