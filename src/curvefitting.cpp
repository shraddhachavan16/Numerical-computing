#include "curvefitting.h"

CurveFitting::CurveFitting(const Matrix &m) : Matrix(m) {}

void CurveFitting::check(std::ofstream &fout) const
{
    if((cols - 1) >= rows)
        fout << "Overfitting condition satisfied\n";
    else
        fout << "No Overfitting\n";
}