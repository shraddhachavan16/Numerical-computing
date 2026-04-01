
// #include <iostream>
// #include <fstream>
// #include <cmath>
// #include "../Include/Gaussian.h"

// using namespace std;

// Gaussian::Gaussian(int size)
// {
//     n = size;
// }

// bool Gaussian::readFile(const string& filename)
// {
//     ifstream fin(filename);
//     if (!fin) return false;

//     int rows, cols;
//     fin >> rows >> cols;

//     A_original.assign(n, vector<double>(n + 1));
//     x.assign(n, 0.0);

//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             fin >> A_original[i][j];

   
//     for (int i = 0; i < n; i++)
//         fin >> A_original[i][n];

//     fin.close();
//     return true;
// }

// const vector<double>& Gaussian::getSolution() const
// {
//     return x;
// }


// NoPivot::NoPivot(int size) : Gaussian(size) {}
// bool NoPivot::solve()
// {
//     A = A_original;
//     for (int k = 0; k < n - 1; k++)
//     {
//         if (fabs(A[k][k]) < 1e-12)
//             return false;

//         for (int i = k + 1; i < n; i++)
//         {
//             double factor = A[i][k] / A[k][k];
//             for (int j = k; j <= n; j++)
//                 A[i][j] -= factor * A[k][j];
//         }
//     }

//     for (int i = n - 1; i >= 0; i--)
//     {
//         double sum = A[i][n];

//         for (int j = i + 1; j < n; j++)
//             sum -= A[i][j] * x[j];

//         if (fabs(A[i][i]) < 1e-12)
//             return false;

//         x[i] = sum / A[i][i];
//     }

//     return true;
// }


// WithPivot::WithPivot(int size) : Gaussian(size) {}

// bool WithPivot::solve()
// {
//     A = A_original;

//     for (int k = 0; k < n - 1; k++)
//     {
//         int maxRow = k;

//         for (int i = k + 1; i < n; i++)
//             if (fabs(A[i][k]) > fabs(A[maxRow][k]))
//                 maxRow = i;

//         if (maxRow != k)
//             swap(A[k], A[maxRow]);

//         if (fabs(A[k][k]) < 1e-12)
//             return false;

//         for (int i = k + 1; i < n; i++)
//         {
//             double factor = A[i][k] / A[k][k];
//             for (int j = k; j <= n; j++)
//                 A[i][j] -= factor * A[k][j];
//         }
//     }

//     for (int i = n - 1; i >= 0; i--)
//     {
//         double sum = A[i][n];

//         for (int j = i + 1; j < n; j++)
//             sum -= A[i][j] * x[j];

//         if (fabs(A[i][i]) < 1e-12)
//             return false;

//         x[i] = sum / A[i][i];
//     }

//     return true;
// }

#include "Gaussian.h"
#include <cmath>

#include <vector>
#include <algorithm>

GaussianNoPivot::GaussianNoPivot(const Matrix &m) : LinearSystem(m){}
GaussianPivot::GaussianPivot(const Matrix &m) : LinearSystem(m){}

void GaussianNoPivot::solve(ofstream &fout)
{
    int n=rows;

    for(int k=0;k<n-1;k++)
    {
        if(fabs((*this)(k,k))<1e-12)
        {
            fout<<"Zero Pivot Error\n";
            return;
        }

        for(int i=k+1;i<n;i++)
        {
            double factor=(*this)(i,k)/(*this)(k,k);

            for(int j=k;j<=n;j++)
                (*this)(i,j)-=factor*(*this)(k,j);
        }
    }

    vector<double> x(n);

    for(int i=n-1;i>=0;i--)
    {
        x[i]=(*this)(i,n);

        for(int j=i+1;j<n;j++)
            x[i]-=(*this)(i,j)*x[j];

        x[i]/=(*this)(i,i);
    }

    fout<<"\nSolution\n";

    for(int i=0;i<n;i++)
        fout<<"x"<<i+1<<" = "<<x[i]<<endl;
}

void GaussianPivot::solve(ofstream &fout)
{
    int n=rows;

    for(int k=0;k<n-1;k++)
    {
        int maxRow=k;
        double maxVal=fabs((*this)(k,k));

        for(int i=k+1;i<n;i++)
        {
            if(fabs((*this)(i,k))>maxVal)
            {
                maxVal=fabs((*this)(i,k));
                maxRow=i;
            }
        }

        if(fabs((*this)(maxRow,k))<1e-12)
        {
            fout<<"Matrix is singular\n";
            return;
        }

        if(maxRow!=k)
        {
            for(int j=0;j<=n;j++)
                swap((*this)(k,j),(*this)(maxRow,j));
        }

        for(int i=k+1;i<n;i++)
        {
            double factor=(*this)(i,k)/(*this)(k,k);

            for(int j=k;j<=n;j++)
                (*this)(i,j)-=factor*(*this)(k,j);
        }
    }

    vector<double> x(n);

    for(int i=n-1;i>=0;i--)
    {
        x[i]=(*this)(i,n);

        for(int j=i+1;j<n;j++)
            x[i]-=(*this)(i,j)*x[j];

        x[i]/=(*this)(i,i);
    }

    fout<<"\nSolution\n";

    for(int i=0;i<n;i++)
        fout<<"x"<<i+1<<" = "<<x[i]<<endl;
}

// g++ main1.cpp src/Gaussian.cpp src/LinearSystem.cpp src/Matrix.cpp src/Lu.cpp -I Include -o NC