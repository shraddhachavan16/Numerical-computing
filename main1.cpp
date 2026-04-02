// // #include <iostream>
// // #include <fstream>

// // #include "Matrix.h"
// // #include "Gaussian.h"
// // #include "Lu.h"
// // #include "Jacobi.h"
// // #include "GaussSeidel.h"
// // #include "LinearSystem.h"
// // #include "Iterative.h"

// // using namespace std;

// // int main()
// // {
// //     ifstream fin("input.txt");
// //     ofstream fout("output.txt");

// //     if(!fin)
// //     {
// //         cout<<"Error opening input.txt\n";
// //         return 1;
// //     }

// //     Matrix m;
// //     m.readFromFile(fin);

// //     // ===== INPUT MATRIX =====
// //     fout<<"=========== INPUT MATRIX ===========\n";
// //     m.displayToFile(fout);

// //     // ===== MATRIX PROPERTIES =====
// //     fout<<"\n=========== MATRIX PROPERTIES ===========\n";

// //     fout<<"Square: "<<(m.isSquare() ? "YES" : "NO")<<"\n";
// //     fout<<"Symmetric: "<<(m.isSymmetric() ? "YES" : "NO")<<"\n";
// //     fout<<"Diagonal: "<<(m.isDiagonal() ? "YES" : "NO")<<"\n";
// //     fout<<"Identity: "<<(m.isIdentity() ? "YES" : "NO")<<"\n";
// //     fout<<"Null: "<<(m.isNull() ? "YES" : "NO")<<"\n";
// //     fout<<"Diagonally Dominant: "<<(m.isDiagonallyDominant() ? "YES" : "NO")<<"\n";

// //     fout<<"========================================\n";

// //     int choice;

// //     cout<<"\n=========== LINEAR SYSTEM SOLVER ===========\n";
// //     cout<<"1. Addition\n";
// //     cout<<"2. Subtraction\n";
// //     cout<<"3. Multiplication\n";
// //     cout<<"4. Transpose\n";
// //     cout<<"5. Determinant\n";
// //     cout<<"6. Inverse\n";
// //     cout<<"7. Gaussian Elimination (No Pivot)\n";
// //     cout<<"8. Gaussian Elimination (Pivot)\n";
// //     cout<<"9. LU Decomposition (Doolittle)\n";
// //     cout<<"10. LU Decomposition (Crout)\n";
// //     cout<<"11. LU Decomposition (Cholesky)\n";
// //     cout<<"12. Jacobi Method\n";
// //     cout<<"13.Gauss seidel method\n";
    
// //     cout<<"0. Exit\n";

// //     cout<<"\nEnter choice: ";
// //     cin>>choice;

// //     LinearSystem* solver = nullptr;

// //     switch(choice)
// //     {
// //         case 1:
// //             fout<<"\nAddition Result:\n"<<(m + m);
// //             break;

// //         case 2:
// //             fout<<"\nSubtraction Result:\n"<<(m - m);
// //             break;

// //         case 3:
// //             fout<<"\nMultiplication Result:\n"<<(m * m);
// //             break;

// //         case 4:
// //             fout<<"\nTranspose Matrix:\n"<<m.transpose();
// //             break;

// //         case 5:
// //             if(!m.isSquare())
// //             {
// //                 cout<<"Determinant only for square matrix\n";
// //                 return 0;
// //             }
// //             fout<<"\nDeterminant = "<<m.determinant()<<"\n";
// //             break;

// //         case 6:
// //             if(!m.isSquare())
// //             {
// //                 cout<<"Inverse only for square matrix\n";
// //                 return 0;
// //             }
// //             fout<<"\nInverse Matrix:\n"<<m.inverse();
// //             break;

// //         case 7:
// //             solver = new GaussianNoPivot(m);
// //             break;

// //         case 8:
// //             solver = new GaussianPivot(m);
// //             break;

// //         case 9:
// //             solver = new LUDoolittle(m);
// //             break;

// //         case 10:
// //             solver = new LUCrout(m);
// //             break;

// //         case 11:
// //             solver = new LUCholesky(m);
// //             break;

// //         case 12:
// //         {
// //             if(!m.isDiagonallyDominant())
// //             {
// //                 cout<<"Matrix not suitable for Jacobi. Using Gaussian Pivot instead.\n";
// //                 fout<<"\nMatrix not suitable for Jacobi. Using Gaussian Pivot instead.\n";

// //                 solver = new GaussianPivot(m);
// //             }
// //             else
// //             {
// //                 solver = new Jacobi(m);
// //             }
// //             break;
// //         }

// //         case 13:
// //             {
// //                 if(!m.isDiagonallyDominant())
// //                 {
// //                     cout<<"Matrix not suitable for Gauss-Seidel. Using Gaussian Pivot instead.\n";
// //                     fout<<"\nMatrix not suitable for Gauss-Seidel. Using Gaussian Pivot instead.\n";

// //                     solver = new GaussianPivot(m);
// //                 }
// //                 else
// //                 {
// //                     solver = new GaussSeidel(m);
// //                 }
// //                 break;
// //             }

// //         case 0:
// //             cout<<"Program exited\n";
// //             return 0;

// //         default:
// //             cout<<"Invalid choice\n";
// //             return 0;
// //     }

// //     // ===== SOLVER EXECUTION =====
// //     if(solver != nullptr)
// //     {
// //         solver->solve(fout);
// //         delete solver;
// //     }

// //     cout<<"\nComputation finished.\n";
// //     cout<<"Check output.txt\n";

// //     return 0;
// // }

// #include <iostream>
// #include <fstream>

// #include "Matrix.h"
// #include "Gaussian.h"
// #include "Lu.h"
// #include "Jacobi.h"
// #include "GaussSeidel.h"
// #include "LinearSystem.h"
// #include "Iterative.h"

// using namespace std;

// int main()
// {
//     ifstream fin("input.txt");
//     ofstream fout("output.txt");

//     if(!fin)
//     {
//         cout<<"Error opening input.txt\n";
//         return 1;
//     }

//     Matrix m;
//     m.readFromFile(fin);

//     // ===== INPUT MATRIX =====
//     fout<<"=========== INPUT MATRIX ===========\n";
//     m.displayToFile(fout);

//     // ===== MATRIX PROPERTIES =====
//     fout<<"\n=========== MATRIX PROPERTIES ===========\n";

//     fout<<"Square: "<<(m.isSquare() ? "YES" : "NO")<<"\n";
//     fout<<"Symmetric: "<<(m.isSymmetric() ? "YES" : "NO")<<"\n";
//     fout<<"Diagonal: "<<(m.isDiagonal() ? "YES" : "NO")<<"\n";
//     fout<<"Identity: "<<(m.isIdentity() ? "YES" : "NO")<<"\n";
//     fout<<"Null: "<<(m.isNull() ? "YES" : "NO")<<"\n";
//     fout<<"Diagonally Dominant: "<<(m.isDiagonallyDominant() ? "YES" : "NO")<<"\n";

//     fout<<"========================================\n";

//     int choice;

//     cout<<"\n=========== LINEAR SYSTEM SOLVER ===========\n";
//     cout<<"1. Addition\n";
//     cout<<"2. Subtraction\n";
//     cout<<"3. Multiplication\n";
//     cout<<"4. Transpose\n";
//     cout<<"5. Determinant\n";
//     cout<<"6. Inverse\n";
//     cout<<"7. Gaussian Elimination (No Pivot)\n";
//     cout<<"8. Gaussian Elimination (Pivot)\n";
//     cout<<"9. LU Decomposition (Doolittle)\n";
//     cout<<"10. LU Decomposition (Crout)\n";
//     cout<<"11. LU Decomposition (Cholesky)\n";
//     cout<<"12. Jacobi Method\n";
//     cout<<"13. Gauss Seidel Method\n";
//     cout<<"14. Gershgorin Theorem\n";
//     cout<<"0. Exit\n";

//     cout<<"\nEnter choice: ";
//     cin>>choice;

//     LinearSystem* solver = nullptr;

//     switch(choice)
//     {
//         case 1:
//             fout<<"\nAddition Result:\n"<<(m + m);
//             break;

//         case 2:
//             fout<<"\nSubtraction Result:\n"<<(m - m);
//             break;

//         case 3:
//             fout<<"\nMultiplication Result:\n"<<(m * m);
//             break;

//         case 4:
//             fout<<"\nTranspose Matrix:\n"<<m.transpose();
//             break;

//         case 5:
//             if(!m.isSquare())
//             {
//                 cout<<"Determinant only for square matrix\n";
//                 return 0;
//             }
//             fout<<"\nDeterminant = "<<m.determinant()<<"\n";
//             break;

//         case 6:
//             if(!m.isSquare())
//             {
//                 cout<<"Inverse only for square matrix\n";
//                 return 0;
//             }
//             fout<<"\nInverse Matrix:\n"<<m.inverse();
//             break;

//         case 7:
//             solver = new GaussianNoPivot(m);
//             break;

//         case 8:
//             solver = new GaussianPivot(m);
//             break;

//         case 9:
//             solver = new LUDoolittle(m);
//             break;

//         case 10:
//             solver = new LUCrout(m);
//             break;

//         case 11:
//             solver = new LUCholesky(m);
//             break;

//         case 12:
//         {
//             if(!m.isDiagonallyDominant())
//             {
//                 cout<<"Matrix is not diagonally dominant → Jacobi may not converge.\n";
//                 cout<<"Using Gaussian Pivot instead.\n";

//                 fout<<"\nMatrix is not diagonally dominant → Jacobi may not converge.\n";
//                 fout<<"Using Gaussian Pivot instead.\n";

//                 solver = new GaussianPivot(m);
//             }
//             else
//             {
//                 solver = new Jacobi(m);
//             }
//             break;
//         }

//         case 13:
//         {
//             if(!m.isDiagonallyDominant())
//             {
//                 cout<<"Matrix is not diagonally dominant → Gauss-Seidel may not converge.\n";
//                 cout<<"Using Gaussian Pivot instead.\n";

//                 fout<<"\nMatrix is not diagonally dominant → Gauss-Seidel may not converge.\n";
//                 fout<<"Using Gaussian Pivot instead.\n";

//                 solver = new GaussianPivot(m);
//             }
//             else
//             {
//                 solver = new GaussSeidel(m);
//             }
//             break;
//         }

//         // case 14:
//         //     m.gershgorinDiscs(fout);
//         //     break;
//     case 14:
//     {
//         Matrix coeff = m.getCoefficientMatrix();
//         coeff.gershgorinDiscs(fout);
//         break;
//         }
//         case 0:
//             cout<<"Program exited\n";
//             return 0;

//         default:
//             cout<<"Invalid choice\n";
//             return 0;
//     }

//     // ===== SOLVER EXECUTION =====
//     if(solver != nullptr)
//     {
//         solver->solve(fout);
//         delete solver;
//     }

//     cout<<"\nComputation finished.\n";
//     cout<<"Check output.txt\n";

//     return 0;
// }

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

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if(!fin)
    {
        cout<<"Error opening input.txt\n";
        return 1;
    }

    Matrix m;
    m.readFromFile(fin);

    // ===== INPUT MATRIX =====
    fout<<"=========== INPUT MATRIX ===========\n";
    m.displayToFile(fout);

    // ===== MATRIX PROPERTIES =====
    fout<<"\n=========== MATRIX PROPERTIES ===========\n";

    fout<<"Square: "<<(m.isSquare() ? "YES" : "NO")<<"\n";
    fout<<"Symmetric: "<<(m.isSymmetric() ? "YES" : "NO")<<"\n";
    fout<<"Diagonal: "<<(m.isDiagonal() ? "YES" : "NO")<<"\n";
    fout<<"Identity: "<<(m.isIdentity() ? "YES" : "NO")<<"\n";
    fout<<"Null: "<<(m.isNull() ? "YES" : "NO")<<"\n";
    fout<<"Diagonally Dominant: "<<(m.isDiagonallyDominant() ? "YES" : "NO")<<"\n";

    fout<<"========================================\n";

    int choice;

    cout<<"\n=========== LINEAR SYSTEM SOLVER ===========\n";
    cout<<"1. Addition\n";
    cout<<"2. Subtraction\n";
    cout<<"3. Multiplication\n";
    cout<<"4. Transpose\n";
    cout<<"5. Determinant\n";
    cout<<"6. Inverse\n";
    cout<<"7. Gaussian Elimination (No Pivot)\n";
    cout<<"8. Gaussian Elimination (Pivot)\n";
    cout<<"9. LU Decomposition (Doolittle)\n";
    cout<<"10. LU Decomposition (Crout)\n";
    cout<<"11. LU Decomposition (Cholesky)\n";
    cout<<"12. Jacobi Method\n";
    cout<<"13. Gauss Seidel Method\n";
    cout<<"14. Gershgorin Theorem\n";
    cout<<"0. Exit\n";

    cout<<"\nEnter choice: ";
    cin>>choice;

    LinearSystem* solver = nullptr;

    switch(choice)
    {
        case 1:
            fout<<"\nAddition Result:\n"<<(m + m);
            break;

        case 2:
            fout<<"\nSubtraction Result:\n"<<(m - m);
            break;

        case 3:
            fout<<"\nMultiplication Result:\n"<<(m * m);
            break;

        case 4:
            fout<<"\nTranspose Matrix:\n"<<m.transpose();
            break;

        case 5:
            if(!m.isSquare())
            {
                cout<<"Determinant only for square matrix\n";
                return 0;
            }
            fout<<"\nDeterminant = "<<m.determinant()<<"\n";
            break;

        case 6:
            if(!m.isSquare())
            {
                cout<<"Inverse only for square matrix\n";
                return 0;
            }
            fout<<"\nInverse Matrix:\n"<<m.inverse();
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
                cout<<"Matrix is not diagonally dominant → Jacobi may not converge.\n";
                cout<<"Using Gaussian Pivot instead.\n";

                fout<<"\nMatrix is not diagonally dominant → Jacobi may not converge.\n";
                fout<<"Using Gaussian Pivot instead.\n";

                solver = new GaussianPivot(m);
            }
            else
            {
                solver = new Jacobi(m);
            }
            break;
        }

        case 13:
        {
            if(!m.isDiagonallyDominant())
            {
                cout<<"Matrix is not diagonally dominant → Gauss-Seidel may not converge.\n";
                cout<<"Using Gaussian Pivot instead.\n";

                fout<<"\nMatrix is not diagonally dominant → Gauss-Seidel may not converge.\n";
                fout<<"Using Gaussian Pivot instead.\n";

                solver = new GaussianPivot(m);
            }
            else
            {
                solver = new GaussSeidel(m);
            }
            break;
        }

        // 🔥 FIXED PART
        case 14:
        {
            Matrix coeff = m.getCoefficientMatrix(); // remove RHS column
            Gershgorin g(coeff);                     // use inheritance
            g.gershgorinTheorem(fout);               // call function
            break;
        }

        case 0:
            cout<<"Program exited\n";
            return 0;

        default:
            cout<<"Invalid choice\n";
            return 0;
    }

    // ===== SOLVER EXECUTION =====
    if(solver != nullptr)
    {
        solver->solve(fout);
        delete solver;
    }

    cout<<"\nComputation finished.\n";
    cout<<"Check output.txt\n";

    return 0;
}