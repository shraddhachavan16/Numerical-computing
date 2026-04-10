#include "Lagrange.h"
#include <cmath>
#include <iomanip>

using namespace std;

// ✅ fixed constructor
Lagrange::Lagrange(const Matrix &m) : Interpolation(m) {}

double Lagrange::interpolate(double value)
{
    double result = 0.0;

    for(int i = 0; i < rows; i++)
    {
        double term = data[i][1];   // y

        for(int j = 0; j < rows; j++)
        {
            if(i != j)
            {
                term *= (value - data[j][0]) /
                        (data[i][0] - data[j][0]);
            }
        }

        result += term;
    }

    return result;
}

void Lagrange::printPolynomial(ofstream &fout)
{
    fout << fixed << setprecision(4);

    fout << "\n--- LAGRANGE INTERPOLATION METHOD ---\n\n";

    // ✅ Given Points
    fout << "Given Points:\n";
    for(int i = 0; i < rows; i++)
    {
        fout << "(" << data[i][0] << ", " << data[i][1] << ")\n";
    }

    // ✅ Formula
    fout << "\nStep 1: Formula\n";
    fout << "P(x) = Σ [ y_i * L_i(x) ]\n";

    // ✅ Basis Polynomials
    fout << "\nStep 2: Basis Polynomials\n";

    for(int i = 0; i < rows; i++)
    {
        fout << "L" << i << "(x) = ";

        // numerator
        for(int j = 0; j < rows; j++)
        {
            if(i != j)
            {
                fout << "(x - " << data[j][0] << ")";
            }
        }

        fout << " / (";

        double denom = 1;

        // denominator
        for(int j = 0; j < rows; j++)
        {
            if(i != j)
            {
                fout << "(" << data[i][0] << " - " << data[j][0] << ")";
                denom *= (data[i][0] - data[j][0]);
            }
        }

        fout << ") = " << denom << "\n";
    }

    // ✅ Final Polynomial
    fout << "\nStep 3: Interpolating Polynomial\n";
    fout << "P(x) = ";

    for(int i = 0; i < rows; i++)
    {
        fout << data[i][1] << "*L" << i << "(x)";
        if(i != rows - 1)
            fout << " + ";
    }

    fout << "\n";
}