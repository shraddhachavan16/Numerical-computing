#include <iostream>
#include "complex.h"

using namespace std;

int main() {
    Complex c1, c2, r;

    cout << "Enter first complex number:\n";
    c1.input();

    cout << "\nEnter second complex number:\n";
    c2.input();

    cout << "\nAddition = ";
    r = c1.add(c2);
    r.show();

    cout << "\nSubtraction = ";
    r = c1.sub(c2);
    r.show();

    cout << "\nMultiplication = ";
    r = c1.mul(c2);
    r.show();

    cout << "\nDivision = ";
    r = c1.div(c2);
    r.show();

    cout << "\n\nNorm of first = " << c1.norm();
    cout << "\nNorm of second = " << c2.norm();

    return 0;
}