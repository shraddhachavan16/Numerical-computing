#include "LeastSquare.h"
#include <cmath>
#include <iomanip>

using namespace std;

LeastSquares::LeastSquares(const Matrix &m) : CurveFitting(m) {}

void LeastSquares::compute(ofstream &fout, int degree)
{
    if(rows == 0 || cols < 2)
    {
        fout << "Invalid data\n";
        return;
    }

    if(degree < 1)
    {
        fout << "Degree must be >= 1\n";
        return;
    }

    fout << fixed << setprecision(4);

  
    vector<vector<double>> A(degree+1, vector<double>(degree+2, 0));

    
    for(int i = 0; i <= degree; i++)
    {
        for(int j = 0; j <= degree; j++)
        {
            for(int k = 0; k < rows; k++)
            {
                A[i][j] += pow(data[k][0], i + j);
            }
        }

        for(int k = 0; k < rows; k++)
        {
            A[i][degree+1] += data[k][1] * pow(data[k][0], i);
        }
    }

  
    for(int i = 0; i <= degree; i++)
    {
        double pivot = A[i][i];

        if(pivot == 0)
        {
            fout << "Singular matrix\n";
            return;
        }

        for(int j = i; j <= degree+1; j++)
            A[i][j] /= pivot;

        for(int k = 0; k <= degree; k++)
        {
            if(k != i)
            {
                double factor = A[k][i];
                for(int j = i; j <= degree+1; j++)
                    A[k][j] -= factor * A[i][j];
            }
        }
    }

    
    fout << "\nCoefficients:\n";
    for(int i = 0; i <= degree; i++)
    {
        fout << "a" << i << " = " << A[i][degree+1] << "\n";
    }

    fout << "\nEquation:\ny = ";
    for(int i = 0; i <= degree; i++)
    {
        double c = A[i][degree+1];

        if(i == 0)
            fout << c;
        else
        {
            if(c >= 0) fout << " + ";
            else fout << " - ";

            fout << fabs(c) << "x^" << i;
        }
    }

   
    double err = 0;

    for(int i = 0; i < rows; i++)
    {
        double x = data[i][0];
        double y = data[i][1];

        double yp = 0;

        for(int j = 0; j <= degree; j++)
        {
            yp += A[j][degree+1] * pow(x, j);
        }

        err += (y - yp) * (y - yp);
    }

    fout << "\n\nRMS Error: " << sqrt(err / rows) << "\n";
}