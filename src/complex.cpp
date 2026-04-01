#include <iostream>
#include <cmath>
// #include "complex.h"
#include "../Include/complex.h"

using namespace std;

// Input
void Complex::input() {
    cout << "Enter real and imaginary: ";
    cin >> real >> imag;
}

// Display
void Complex::show() {
    if (imag >= 0)
        cout << real << " + " << imag << "i";
    else
        cout << real << " - " << -imag << "i";
}

// Addition
Complex Complex::add(Complex c) {
    Complex t;
    t.real = real + c.real;
    t.imag = imag + c.imag;
    return t;
}

// Subtraction
Complex Complex::sub(Complex c) {
    Complex t;
    t.real = real - c.real;
    t.imag = imag - c.imag;
    return t;
}

// Multiplication
Complex Complex::mul(Complex c) {
    Complex t;
    t.real = (real * c.real) - (imag * c.imag);
    t.imag = (real * c.imag) + (imag * c.real);
    return t;
}

// Division
Complex Complex::div(Complex c) {
    Complex t;
    float d = (c.real * c.real) + (c.imag * c.imag);

    t.real = ((real * c.real) + (imag * c.imag)) / d;
    t.imag = ((imag * c.real) - (real * c.imag)) / d;

    return t;
}

// Norm
float Complex::norm() {
    return sqrt(real * real + imag * imag);
}