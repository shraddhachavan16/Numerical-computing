#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    try
    {
        int r, c;

        // ===== Matrix A =====
        cout << "Enter rows and columns: ";
        cin >> r >> c;

        Matrix A(r, c);

        cout << "\nEnter Matrix A:\n";
        A.read();

        // Copy Constructor
        Matrix B = A;

        cout << "\nMatrix B (Copy of A):\n";
        B.display();


        // ===== Matrix C =====
        Matrix C(r, c);

        cout << "\nEnter Matrix C:\n";
        C.read();


        // Addition
        Matrix sum = A.add(C);
        cout << "\naddition:\n";
        sum.display();


        // Subtraction
        Matrix diff = A.sub(C);
        cout << "\nsubstraction:\n";
        diff.display();


        // ===== Gaussian Elimination =====
        int n;

        cout << "\nEnter number of variables: ";
        cin >> n;

        Matrix G(n, n + 1);

        cout << "\nEnter Augmented Matrix:\n";
        G.read();


        // Copy before solving
        Matrix Gcopy = G;

        cout << "\nSolving using Gaussian Elimination:\n";
        Gcopy.gaussianElimination();
    }
    catch(const char* msg)
    {
        cout << "\nError: " << msg << endl;
    }

    return 0;
}