#include "LeastSquare.h"
#include <cmath>

LeastSquares::LeastSquares(const Matrix &m): Overfitting(m) {}

void LeastSquares::compute(std::ofstream &fout)
{
    double sx=0, sy=0, sxy=0, sx2=0;
    int n = rows;

    // Step 1: sums
    for(int i=0;i<n;i++)
    {
        double x = data[i][0];
        double y = data[i][1];

        sx  += x;
        sy  += y;
        sxy += x*y;
        sx2 += x*x;
    }

    // Step 2: coefficients
    double a = (n*sxy - sx*sy) / (n*sx2 - sx*sx);
    double b = (sy - a*sx) / n;

    fout << "\nLine: y = " << a << "x + " << b << "\n";

    // Step 3: RMS
    double err = 0;

    for(int i=0;i<n;i++)
    {
        double x = data[i][0];
        double y = data[i][1];

        double yp = a*x + b;
        double d  = y - yp;

        err += d*d;
    }

    fout << "RMS Error = " << sqrt(err/n) << "\n";
}