#include "Gershgorin.h"
#include <cmath>
#include <iostream>

using namespace std;

// Constructor
Gershgorin::Gershgorin(const Matrix &m) : Eigen(m)
{
}

void Gershgorin::gershgorinTheorem(ofstream &fout)
{
    fout << "\n===== Gershgorin Theorem =====\n";

    for(int i = 0; i < n; i++)
    {
        double center = (*this)(i,i);
        double radius = 0;

        for(int j = 0; j < n; j++)
        {
            if(i != j)
                radius += fabs((*this)(i,j));
        }

        fout << "Disc " << i+1 << ":\n";
        fout << "Center = " << center << "\n";
        fout << "Radius = " << radius << "\n";

        fout << "Eigenvalues lie in: ["
             << center - radius << ", "
             << center + radius << "]\n\n";
    }

    fout << "All eigenvalues lie within these discs.\n";

    if(isDiagonallyDominant())
        fout << "Matrix is diagonally dominant → good for iterative methods\n";
}