#include "Interpolation.h"
#include <iostream>

using namespace std;

Interpolation::Interpolation(const Matrix &m) : Matrix(m)
{
    if(rows <= 0 || cols < 2)
    {
        cout << "Invalid interpolation data!\n";
        exit(1);
    }
}

void Interpolation::displayData(ofstream &fout) const
{
    fout << "Given Points:\n";

    for(int i = 0; i < rows; i++)
    {
        fout << "(" << data[i][0] << ", " << data[i][1] << ")\n";
    }
}