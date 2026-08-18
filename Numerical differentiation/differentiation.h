#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H
#include <string>
using namespace std;


class TestFunction
{
public:
    virtual double value(double x) const = 0;
    virtual double exactDerivative(double x) const = 0;
    virtual string name() const = 0;

    virtual ~TestFunction() {}
};

// Example 1: f(x) = e^x

class Exponential : public TestFunction
{
public:
    double value(double x) const override;
    double exactDerivative(double x) const override;
    string name() const override;
};

// Example 2: f(x) = sin(x)
class Sine : public TestFunction
{
public:
    double value(double x) const override;
    double exactDerivative(double x) const override;
    string name() const override;
};
// Example 3: f(x) = x^3 - 2x + 1
class Polynomial : public TestFunction
{
public:
    double value(double x) const override;
    double exactDerivative(double x) const override;
    string name() const override;
};

// Base class for numerical differentiation
class Differentiation
{
protected:
    double x;
    double h;

public:
    Differentiation(double x, double h);
    virtual double calculate(
    const TestFunction& function) const = 0;
    virtual ~Differentiation() {}
};

// Forward Difference

class ForwardDifference : public Differentiation
{
public:
    ForwardDifference(double x, double h);

    double calculate(
        const TestFunction& function) const override;
};

// Backward Difference

class BackwardDifference : public Differentiation
{
public:
    BackwardDifference(double x, double h);

    double calculate(
        const TestFunction& function) const override;
};

// Central Difference

class CentralDifference : public Differentiation
{
public:
    CentralDifference(double x, double h);

    double calculate(
        const TestFunction& function) const override;
};

#endif