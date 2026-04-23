#include <iostream>
#include <fstream>

#include "Matrix.h"
#include "Gaussian.h"
#include "Lu.h"
#include "Jacobi.h"
#include "GaussSeidel.h"
#include "LinearSystem.h"
#include "Iterative.h"
#include "Eigen.h"
#include "Gershgorin.h"
#include "Lagrange.h"

// ✅ YOUR FILES (fixed case)
#include "CurveFitting.h"
#include "LeastSquare.h"

#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if(!fin)
    {
        cout << "Error opening input.txt\n";
        return 1;
    }

    Matrix m;
    m.readFromFile(fin);

    // ===== DISPLAY INPUT =====
    fout << "=========== INPUT MATRIX ===========\n";
    m.displayToFile(fout);

    // ===== PROPERTIES =====
    fout << "\n=========== MATRIX PROPERTIES ===========\n";

    fout << "Square: " << (m.isSquare() ? "YES" : "NO") << "\n";
    fout << "Symmetric: " << (m.isSymmetric() ? "YES" : "NO") << "\n";
    fout << "Diagonal: " << (m.isDiagonal() ? "YES" : "NO") << "\n";
    fout << "Identity: " << (m.isIdentity() ? "YES" : "NO") << "\n";
    fout << "Null: " << (m.isNull() ? "YES" : "NO") << "\n";
    fout << "Diagonally Dominant: " << (m.isDiagonallyDominant() ? "YES" : "NO") << "\n";

    fout << "========================================\n";

    int choice;

    cout << "\n=========== MENU ===========\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Transpose\n";
    cout << "5. Determinant\n";
    cout << "6. Inverse\n";
    cout << "7. Gaussian Elimination (No Pivot)\n";
    cout << "8. Gaussian Elimination (Pivot)\n";
    cout << "9. LU Decomposition (Doolittle)\n";
    cout << "10. LU Decomposition (Crout)\n";
    cout << "11. LU Decomposition (Cholesky)\n";
    cout << "12. Jacobi Method\n";
    cout << "13. Gauss Seidel Method\n";
    cout << "14. Gershgorin Theorem\n";
    cout << "15. Lagrange Interpolation\n";
    cout << "16. Least Squares (Curve Fitting)\n";
    cout << "0. Exit\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    LinearSystem* solver = nullptr;

    switch(choice)
    {
        case 1:
            fout << "\nAddition Result:\n" << (m + m);
            break;

        case 2:
            fout << "\nSubtraction Result:\n" << (m - m);
            break;

        case 3:
            fout << "\nMultiplication Result:\n" << (m * m);
            break;

        case 4:
            fout << "\nTranspose Matrix:\n" << m.transpose();
            break;

        case 5:
            if(!m.isSquare())
            {
                cout << "Determinant only for square matrix\n";
                return 0;
            }
            fout << "\nDeterminant = " << m.determinant() << "\n";
            break;

        case 6:
            if(!m.isSquare())
            {
                cout << "Inverse only for square matrix\n";
                return 0;
            }
            fout << "\nInverse Matrix:\n" << m.inverse();
            break;

        case 7:
            solver = new GaussianNoPivot(m);
            break;

        case 8:
            solver = new GaussianPivot(m);
            break;

        case 9:
            solver = new LUDoolittle(m);
            break;

        case 10:
            solver = new LUCrout(m);
            break;

        case 11:
            solver = new LUCholesky(m);
            break;

        case 12:
        {
            if(!m.isDiagonallyDominant())
            {
                cout << "Matrix not suitable for Jacobi → using Gaussian Pivot\n";
                fout << "Matrix not suitable for Jacobi → using Gaussian Pivot\n";
                solver = new GaussianPivot(m);
            }
            else
            {
                Jacobi jb(m);
                vector<double> res = jb.solve();

                fout << "\nSolution (Jacobi):\n";
                for(int i = 0; i < res.size(); i++)
                    fout << "x" << i+1 << " = " << res[i] << endl;
            }
            break;
        }

        case 13:
        {
            if(!m.isDiagonallyDominant())
            {
                cout << "Matrix not suitable for Gauss-Seidel → using Gaussian Pivot\n";
                fout << "Matrix not suitable for Gauss-Seidel → using Gaussian Pivot\n";
                solver = new GaussianPivot(m);
            }
            else
            {
                GaussSeidel gs(m);
                vector<double> res = gs.solve();

                fout << "\nSolution (Gauss-Seidel):\n";
                for(int i = 0; i < res.size(); i++)
                    fout << "x" << i+1 << " = " << res[i] << endl;
            }
            break;
        }

        case 14:
        {
            Matrix coeff = m.getCoefficientMatrix();
            Gershgorin g(coeff);
            g.gershgorinTheorem(fout);
            break;
        }

        case 15:
        {
            Lagrange obj(m);

            double x;
            cout << "Enter value of x: ";
            cin >> x;

            double fx = obj.interpolate(x);

            fout << "\n===== LAGRANGE INTERPOLATION =====\n\n";
            obj.displayData(fout);
            obj.printPolynomial(fout);

            fout << "\nFor x = " << x << ":\n";
            fout << "f(" << x << ") = " << fx << "\n";
            break;
        }

        case 16:
        {
            int degree;

            cout << "\nEnter polynomial degree: ";
            cin >> degree;

           
            CurveFitting* obj = new LeastSquares(m);

            obj->check(fout);
            obj->compute(fout, degree);

            delete obj;
            break;
        }

        case 0:
            cout << "Program exited\n";
            return 0;

        default:
            cout << "Invalid choice\n";
            return 0;
    }

    if(solver != nullptr)
    {
        solver->solve(fout);
        delete solver;
    }

    cout << "\nComputation finished.\n";
    cout << "Check output.txt\n";

    return 0;
}