#include <iostream>
#include <cmath>
#include "../include/function.h"
using namespace std;

double f(double x)
{
    return 4*x*x*x - 3*x;
}

double df(double x)
{
    return 12*x*x - 3;
}

double g(double x)
{
    return sqrt(3.0)/2.0;   
}


RootMethod::RootMethod()
{
    tol = 0.0001;   
}

double a, b, m;
Bisection::Bisection()
{
    for (a = 0; a < 1; a += 0.1)
    {
        b = a + 0.1;

        if (f(a)*f(b) < 0)
            break;
    }
}

void Bisection::solve()
{
    do
    {
        m = (a + b) / 2;

        if (f(a)*f(m) < 0)
            b = m;
        else
            a = m;

    } while (fabs(f(m)) >= tol);

    cout << "Bisection = " << m << endl;
}


double x;
Newton::Newton()
{
    x = 0.8;
}

void Newton::solve()
{
    double x_old;

    do
    {
        x_old = x;
        x = x - f(x)/df(x);

    } while (fabs(x - x_old) >= tol);

    cout << "Newton = " << x << endl;
}





double y;
FixedPoint::FixedPoint()
{
    y = 0.8;
}

void FixedPoint::solve()
{
    double y_old;
    do
    {
        y_old = y;
        y = g(y);

    } while (fabs(y - y_old) >= tol);
    cout << "Fixed Point = " << y << endl;
}



