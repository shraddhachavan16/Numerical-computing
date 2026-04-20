#include "overfitting.h"

Overfitting::Overfitting(const Matrix &m) : Matrix(m) {}

void Overfitting::check(std::ofstream &fout) const
{
    if((cols - 1) >= rows)
        fout << "Overfitting condition satisfied\n";
    else
        fout << "No Overfitting\n";
}