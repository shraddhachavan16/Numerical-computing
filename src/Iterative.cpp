// #include "Iterative.h"
// #include <cmath>

// using namespace std;

// Iterative::Iterative(const Matrix &m, int maxIter, double tol)
//     : LinearSystem(m), maxIter(maxIter), tol(tol) {}

// bool Iterative::isDiagonallyDominant()
// {
//     for(int i = 0; i < rows; i++)
//     {
//         double sum = 0;

//         for(int j = 0; j < rows; j++)
//         {
//             if(i != j)
//                 sum += fabs((*this)(i,j));
//         }

//         if(fabs((*this)(i,i)) < sum)
//             return false;
//     }
//     return true;
// }

#include "Iterative.h"

using namespace std;

Iterative::Iterative(const Matrix &m) : LinearSystem(m)
{
    maxIter = 500;
    tol = 0.0001;
}
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
bool Iterative::makeDiagonallyDominant()
{
    for(int i = 0; i < rows; i++)
    {
        int maxRow = i;

        for(int j = i; j < rows; j++)
        {
            if(fabs((*this)(j,i)) > fabs((*this)(maxRow,i)))
                maxRow = j;
        }

        if(maxRow != i)
        {
            for(int k = 0; k <= rows; k++)
                swap((*this)(i,k), (*this)(maxRow,k));
        }
    }

    return isDiagonallyDominant();
}
