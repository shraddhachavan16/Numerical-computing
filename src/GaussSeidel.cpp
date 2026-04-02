#include "GaussSeidel.h"
#include <vector>
#include <cmath>
#include <iostream>

GaussSeidel::GaussSeidel(const Matrix &m) : Iterative(m) {}

std::vector<double> GaussSeidel::solve()
{
    int n = rows;
    std::vector<double> x(n, 0.0);

    if(cols != rows + 1)
    {
        std::cout << "Error: Matrix must be augmented\n";
        return x;
    }

    if(!isDiagonallyDominant())
    {
        std::cout << "Matrix is NOT diagonally dominant\n";

        if(makeDiagonallyDominant())
            std::cout << "Matrix rearranged to diagonally dominant form\n";
        else
            std::cout << "Warning: Cannot make diagonally dominant\n";
    }

    bool converged = false;

    for(int iter = 0; iter < maxIter; iter++)
    {
        double error = 0;

        for(int i = 0; i < n; i++)
        {
            double diag = (*this)(i,i);

            if(fabs(diag) < 1e-12)
            {
                std::cout << "Zero diagonal error\n";
                return x;
            }

            double sum = (*this)(i,n);

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                    sum -= (*this)(i,j) * x[j];
            }

            double newVal = sum / diag;

            double diff = fabs(newVal - x[i]);
            if(diff > error)
                error = diff;

            x[i] = newVal;
        }

        if(error < tol)
        {
            converged = true;
            break;
        }
    }

    if(!converged)
        std::cout << "Warning: Max iterations reached\n";

    return x;
}