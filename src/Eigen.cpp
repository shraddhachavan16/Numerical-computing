#include "Eigen.h"
#include <iostream>

using namespace std;

// Constructor
Eigen::Eigen(const Matrix &m) : Matrix(m)
{
    if(!isSquare())
    {
        cout << "Only square matrix allowed\n";
        exit(1);
    }

    n = getRows();
}