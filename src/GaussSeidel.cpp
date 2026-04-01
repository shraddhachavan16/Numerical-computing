// #include "GaussSeidel.h"
// #include <vector>
// #include <cmath>

// using namespace std;

// // Constructor
// GaussSeidel::GaussSeidel(const Matrix &m) : LinearSystem(m) {}


// // ===============================
// // CHECK DIAGONAL DOMINANCE
// // ===============================
// bool GaussSeidel::isDiagonallyDominant()
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


// // ===============================
// // GAUSS-SEIDEL SOLVER
// // ===============================
void GaussSeidel::solve(ofstream &fout)
{
    int n = rows;
    vector<double> x(n, 0.0);
    if(cols != rows + 1)
    {
        fout << "Error: Matrix must be augmented (n x n+1)\n";
        return;
    }
    if(!isDiagonallyDominant())
    {
        fout << "Warning: Matrix is NOT diagonally dominant.\n";
        fout << "Gauss-Seidel may not converge.\n";
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
                fout << "Error: Zero diagonal at row " << i+1 << endl;
                return;
            }
            double sum = (*this)(i,n);
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                    sum -= (*this)(i,j) * x[j];
            }
            double newVal = sum / diag;
            error = max(error, fabs(newVal - x[i]));
            x[i] = newVal;
        }
        if(error < tol)
        {
            converged = true;
            fout << "\nGauss-Seidel converged in " << iter+1 << " iterations\n";
            break;
        }
        if(error > 1e10)
        {
            fout << "\nGauss-Seidel diverging\n";
            return;
        }
    }
    fout << "\nGauss-Seidel Solution:\n";
    for(int i = 0; i < n; i++)
        fout << "x" << i+1 << " = " << x[i] << endl;
    if(!converged)
        fout << "\nWarning: Max iterations reached\n";
}

#include "GaussSeidel.h"
#include <vector>
#include <cmath>

using namespace std;

GaussSeidel::GaussSeidel(const Matrix &m) : Iterative(m) {}

bool GaussSeidel::isDiagonallyDominant()
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

void GaussSeidel::solve(ofstream &fout)
{
    int n = rows;

    vector<double> x(n, 0.0);

    if(cols != rows + 1)
    {
        fout << "Error: Matrix must be augmented (n x n+1)\n";
        return;
    }

    if(!isDiagonallyDominant())
    {
        fout << "Warning: Matrix is NOT diagonally dominant.\n";
        fout << "Gauss-Seidel may not converge.\n";
    }

    bool converged = false;

    for(int iter = 0; iter < 500; iter++)
    {
        double error = 0;

        for(int i = 0; i < n; i++)
        {
            double diag = (*this)(i,i);

            if(fabs(diag) < 1e-12)
            {
                fout << "Error: Zero diagonal at row " << i+1 << endl;
                return;
            }

            double sum = (*this)(i,n);

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                    sum -= (*this)(i,j) * x[j];
            }

            double newVal = sum / diag;

            // ✅ FIXED ERROR CALCULATION
            error = max(error, fabs(newVal - x[i]));

            x[i] = newVal;   // 🔥 immediate update
        }

        if(error < 1e-6)
        {
            converged = true;
            fout << "\nGauss-Seidel converged in " << iter+1 << " iterations\n";
            break;
        }

        if(error > 1e10)
        {
            fout << "\nGauss-Seidel diverging\n";
            return;
        }
    }

    fout << "\nGauss-Seidel Solution:\n";

    for(int i = 0; i < n; i++)
        fout << "x" << i+1 << " = " << x[i] << endl;

    if(!converged)
        fout << "\nWarning: Max iterations reached\n";
}