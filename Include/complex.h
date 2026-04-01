#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
private:
    float real, imag;

public:
    void input();
    void show();

    Complex add(Complex);
    Complex sub(Complex);
    Complex mul(Complex);
    Complex div(Complex);

    float norm();
};

#endif