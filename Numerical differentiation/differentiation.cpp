#include "Differentiation.h"
#include <cmath>
using namespace std;


// ======================================================
// f(x) = e^x
// f'(x) = e^x
// ======================================================

double Exponential::value(double x) const
{
    return exp(x);
}

double Exponential::exactDerivative(double x) const
{
    return exp(x);
}

string Exponential::name() const
{
    return "e^x";
}


// ======================================================
// Example 2
// f(x) = sin(x)
// f'(x) = cos(x)
// ======================================================

double Sine::value(double x) const
{
    return sin(x);
}

double Sine::exactDerivative(double x) const
{
    return cos(x);
}

string Sine::name() const
{
    return "sin(x)";
}


// ======================================================
// Example 3
// f(x) = x^3 - 2x + 1
// f'(x) = 3x^2 - 2
// ======================================================

double Polynomial::value(double x) const
{
    return x * x * x - 2 * x + 1;
}

double Polynomial::exactDerivative(double x) const
{
    return 3 * x * x - 2;
}

string Polynomial::name() const
{
    return "x^3 - 2x + 1";
}


// ======================================================
// Differentiation constructor
// ======================================================

Differentiation::Differentiation(double x, double h)
{
    this->x = x;
    this->h = h;
}


// ======================================================
// Forward Difference
//
// f'(x) ≈ [f(x+h) - f(x)] / h
// ======================================================

ForwardDifference::ForwardDifference(double x, double h)
    : Differentiation(x, h)
{
}

double ForwardDifference::calculate(
    const TestFunction& function) const
{
    return (function.value(x + h)
          - function.value(x)) / h;
}


// ======================================================
// Backward Difference
//
// f'(x) ≈ [f(x) - f(x-h)] / h
// ======================================================

BackwardDifference::BackwardDifference(double x, double h)
    : Differentiation(x, h)
{
}

double BackwardDifference::calculate(
    const TestFunction& function) const
{
    return (function.value(x)
          - function.value(x - h)) / h;
}


// ======================================================
// Central Difference
//
// f'(x) ≈ [f(x+h) - f(x-h)] / 2h
// ======================================================

CentralDifference::CentralDifference(double x, double h)
    : Differentiation(x, h)
{
}

double CentralDifference::calculate(
    const TestFunction& function) const
{
    return (function.value(x + h)
          - function.value(x - h)) / (2 * h);
}