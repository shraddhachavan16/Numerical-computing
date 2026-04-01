#include "Linearsystem.h"

LinearSystem::LinearSystem(const Matrix &m) : Matrix(m)
{
    n = rows;
}