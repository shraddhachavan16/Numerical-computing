
#include "jacobi.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Jacobi::Jacobi(const Matrix &m) : Iterative(m) {}

bool Jacobi::isDiagonallyDominant()
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

void Jacobi::solve(ofstream &fout)
{
	int n = rows;
	vector<double> x(n, 0.0), x_new(n, 0.0);
	if(cols != rows + 1)
	{
		fout << "Error: Matrix must be augmented (n x n+1)\n";
		return;
	}
	if(!isDiagonallyDominant())
	{
		fout << "Warning: Matrix is NOT diagonally dominant\n";
		fout << "Jacobi may diverge\n";
	}
	bool converged = false;
	for(int iter = 0; iter < maxIter; iter++)
	{
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
			x_new[i] = sum / diag;
		}
		double err = 0;
		for(int i = 0; i < n; i++)
			err = max(err, fabs(x_new[i] - x[i]));
		if(err < tol)
		{
			converged = true;
			fout << "\nJacobi converged in " << iter+1 << " iterations\n";
			break;
		}
		if(err > 1e10)
		{
			fout << "\nJacobi diverging (unstable)\n";
			return;
		}
		x = x_new;
	}
	fout << "\nJacobi Solution:\n";
	for(int i = 0; i < n; i++)
		fout << "x" << i+1 << " = " << x_new[i] << endl;
	if(!converged)
		fout << "\nWarning: Maximum iterations reached\n";
}