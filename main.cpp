#include <iostream>
#include "include/function.h"

using namespace std;

int main()
{
    Bisection b;
    Newton n;
    FixedPoint f;

    b.solve();
    n.solve();
    f.solve();

    return 0;
}
// g++ main.cpp src/function.cpp -I Include -o NC