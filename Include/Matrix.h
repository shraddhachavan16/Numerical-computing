// #ifndef MATRIX_H
// #define MATRIX_H

// #include <iostream>
// using namespace std;

// class Matrix
// {
// private:
//     int rows, cols;
//     float mat[10][10];

// public:
//     // Constructor
//     Matrix(int r = 0, int c = 0);

//     // Copy Constructor
//     Matrix(const Matrix& m);

//     void read();
//     void display() const;

//     Matrix add(const Matrix& m);
//     Matrix sub(const Matrix& m);

//     void gaussianElimination();   // Without Pivoting
//     void backSubstitution();
// };

// #endif

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

class Matrix
{
protected:
    int rows, cols;
    vector<vector<double>> data;

public:
    Matrix();
    Matrix(int r,int c);
    Matrix(const Matrix &m);

    void readFromFile(ifstream &fin);
    void displayToFile(ofstream &fout) const;

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;

    double &operator()(int i,int j);
    double operator()(int i,int j) const;

    bool operator==(const Matrix &m) const;

    friend istream &operator>>(istream &in, Matrix &m);
    friend ostream &operator<<(ostream &out, const Matrix &m);

    bool isSquare() const;
    bool isSymmetric() const;
    bool isIdentity() const;
    bool isNull() const;
    bool isDiagonal() const;
    bool isDiagonallyDominant() const;
    bool isTranspose(const Matrix &m) const;

    void makeDiagonallyDominant();
    Matrix transpose() const;

    double determinant() const;
    Matrix inverse() const;
    int getRows() const { return rows; }
     void gershgorinDiscs(ofstream &fout) const;
    Matrix getCoefficientMatrix() const;
};

#endif