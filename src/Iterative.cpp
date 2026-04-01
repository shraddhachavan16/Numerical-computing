#include "Iterative.h"
#include <cmath>

using namespace std;

Iterative::Iterative(const Matrix &m, int maxIter, double tol)
    : LinearSystem(m), maxIter(maxIter), tol(tol) {}

bool Iterative::isDiagonallyDominant()
{
    for(int i = 0; i < rows; i++)
    {
        double sum = 0;

        for(int j = 0; j < rows; j++)
        {
            if(i != j)
                sum += fabs((*this)(i,j));
        }

        if(fabs((*this)(i,i)) < sum)
            return false;
    }
    return true;
}