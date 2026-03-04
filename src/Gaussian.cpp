
#include <iostream>
#include <fstream>
#include <cmath>
#include "../Include/Gaussian.h"

using namespace std;

Gaussian::Gaussian(int size)
{
    n = size;
}

bool Gaussian::readFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin) return false;

    int rows, cols;
    fin >> rows >> cols;

    A_original.assign(n, vector<double>(n + 1));
    x.assign(n, 0.0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> A_original[i][j];

   
    for (int i = 0; i < n; i++)
        fin >> A_original[i][n];

    fin.close();
    return true;
}

const vector<double>& Gaussian::getSolution() const
{
    return x;
}


NoPivot::NoPivot(int size) : Gaussian(size) {}
bool NoPivot::solve()
{
    A = A_original;
    for (int k = 0; k < n - 1; k++)
    {
        if (fabs(A[k][k]) < 1e-12)
            return false;

        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j <= n; j++)
                A[i][j] -= factor * A[k][j];
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = A[i][n];

        for (int j = i + 1; j < n; j++)
            sum -= A[i][j] * x[j];

        if (fabs(A[i][i]) < 1e-12)
            return false;

        x[i] = sum / A[i][i];
    }

    return true;
}


WithPivot::WithPivot(int size) : Gaussian(size) {}

bool WithPivot::solve()
{
    A = A_original;

    for (int k = 0; k < n - 1; k++)
    {
        int maxRow = k;

        for (int i = k + 1; i < n; i++)
            if (fabs(A[i][k]) > fabs(A[maxRow][k]))
                maxRow = i;

        if (maxRow != k)
            swap(A[k], A[maxRow]);

        if (fabs(A[k][k]) < 1e-12)
            return false;

        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j <= n; j++)
                A[i][j] -= factor * A[k][j];
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = A[i][n];

        for (int j = i + 1; j < n; j++)
            sum -= A[i][j] * x[j];

        if (fabs(A[i][i]) < 1e-12)
            return false;

        x[i] = sum / A[i][i];
    }

    return true;
}