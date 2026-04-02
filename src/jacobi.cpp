#include "Jacobi.h"
#include <vector>
#include <cmath>
#include <iostream>

Jacobi::Jacobi(const Matrix &m) : Iterative(m) {}

std::vector<double> Jacobi::solve()
{
    int n = rows;

    std::vector<double> x(n, 0.0);
    std::vector<double> x_new(n, 0.0);

    if(cols != rows + 1)
    {
        std::cout << "Error: Matrix must be augmented\n";
        return x;
    }

    // Check + fix dominance
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
        // 🔁 compute new values
        for(int i = 0; i < n; i++)
        {
            double sum = (*this)(i,n);
            double diag = (*this)(i,i);

            if(fabs(diag) < 1e-12)
            {
                std::cout << "Zero diagonal error\n";
                return x;
            }

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                    sum -= (*this)(i,j) * x[j];
            }

            x_new[i] = sum / diag;
        }

        // 🔁 calculate error
        double error = 0;
        for(int i = 0; i < n; i++)
        {
            double diff = fabs(x_new[i] - x[i]);
            if(diff > error)
                error = diff;
        }

        if(error < tol)
        {
            converged = true;
            break;
        }

        x = x_new;  // 🔥 Jacobi update after full iteration
    }

    if(!converged)
        std::cout << "Warning: Max iterations reached\n";

    return x;   // ✅ return result
}