#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix
{
private:
    int rows, cols;
    float mat[10][10];

public:
    // Constructor
    Matrix(int r = 0, int c = 0);

    // Copy Constructor
    Matrix(const Matrix& m);

    void read();
    void display() const;

    Matrix add(const Matrix& m);
    Matrix sub(const Matrix& m);

    void gaussianElimination();   // Without Pivoting
    void backSubstitution();
};

#endif