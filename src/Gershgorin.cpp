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

    // ✅ Square matrix check (VERY IMPORTANT)
    if(rows != cols)
    {
        fout << "Error: Matrix must be square for Gershgorin Theorem\n";
        return;
    }

    int n = rows;  // number of rows = columns

    for(int i = 0; i < n; i++)
    {
        double center = (*this)(i,i);  // diagonal element
        double radius = 0;

        // calculate radius (sum of non-diagonal elements)
        for(int j = 0; j < n; j++)
        {
            if(i != j)
                radius += fabs((*this)(i,j));
        }

        // print disc information
        fout << "Disc " << i+1 << ":\n";
        fout << "Center = " << center << "\n";
        fout << "Radius = " << radius << "\n";

        fout << "Eigenvalues lie in: ["
             << center - radius << ", "
             << center + radius << "]\n\n";
    }

    fout << "All eigenvalues lie within these discs.\n";

    // optional: check diagonal dominance
    if(isDiagonallyDominant())
        fout << "Matrix is diagonally dominant → good for iterative methods\n";
}