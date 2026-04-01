#include "Lu.h"
#include <cmath>
#include <vector>

using namespace std;


LUDoolittle::LUDoolittle(const Matrix &m) : LinearSystem(m) {}

void LUDoolittle::solve(ofstream &fout)
{
    int n = rows;

    Matrix L(n,n), U(n,n);

    for(int i=0;i<n;i++)
    {
        for(int k=i;k<n;k++)
        {
            double sum = 0;

            for(int j=0;j<i;j++)
                sum += L(i,j) * U(j,k);

            U(i,k) = (*this)(i,k) - sum;
        }

        for(int k=i;k<n;k++)
        {
            if(i==k)
                L(i,i) = 1;
            else
            {
                double sum = 0;

                for(int j=0;j<i;j++)
                    sum += L(k,j) * U(j,i);

                L(k,i) = ((*this)(k,i) - sum) / U(i,i);
            }
        }
    }

    vector<double> y(n), x(n);

    for(int i=0;i<n;i++)
    {
        y[i] = (*this)(i,n);

        for(int j=0;j<i;j++)
            y[i] -= L(i,j) * y[j];
    }

    for(int i=n-1;i>=0;i--)
    {
        x[i] = y[i];

        for(int j=i+1;j<n;j++)
            x[i] -= U(i,j) * x[j];

        x[i] /= U(i,i);
    }

    fout << "\nL Matrix\n";
    L.displayToFile(fout);

    fout << "\nU Matrix\n";
    U.displayToFile(fout);

    fout << "\nSolution\n";

    for(int i=0;i<n;i++)
        fout << "x" << i+1 << " = " << x[i] << endl;
}


LUCrout::LUCrout(const Matrix &m) : LinearSystem(m) {}

void LUCrout::solve(ofstream &fout)
{
    int n = rows;

    Matrix L(n,n), U(n,n);

    for(int j=0;j<n;j++)
    {
        U(j,j) = 1;

        for(int i=j;i<n;i++)
        {
            double sum = 0;

            for(int k=0;k<j;k++)
                sum += L(i,k) * U(k,j);

            L(i,j) = (*this)(i,j) - sum;
        }

        for(int i=j+1;i<n;i++)
        {
            double sum = 0;

            for(int k=0;k<j;k++)
                sum += L(j,k) * U(k,i);

            U(j,i) = ((*this)(j,i) - sum) / L(j,j);
        }
    }

    vector<double> y(n), x(n);

    for(int i=0;i<n;i++)
    {
        y[i] = (*this)(i,n);

        for(int j=0;j<i;j++)
            y[i] -= L(i,j) * y[j];

        y[i] /= L(i,i);
    }

    for(int i=n-1;i>=0;i--)
    {
        x[i] = y[i];

        for(int j=i+1;j<n;j++)
            x[i] -= U(i,j) * x[j];
    }

    fout << "\nL Matrix\n";
    L.displayToFile(fout);

    fout << "\nU Matrix\n";
    U.displayToFile(fout);

    fout << "\nSolution\n";

    for(int i=0;i<n;i++)
        fout << "x" << i+1 << " = " << x[i] << endl;
}


LUCholesky::LUCholesky(const Matrix &m) : LinearSystem(m) {}

void LUCholesky::solve(ofstream &fout)
{
    int n = rows;

    Matrix L(n,n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            double sum = 0;

            for(int k=0;k<j;k++)
                sum += L(i,k) * L(j,k);

            if(i==j)
                L(i,j) = sqrt((*this)(i,i) - sum);
            else
                L(i,j) = ( (*this)(i,j) - sum ) / L(j,j);
        }
    }

    Matrix Lt = L.transpose();

    vector<double> y(n), x(n);

    for(int i=0;i<n;i++)
    {
        y[i] = (*this)(i,n);

        for(int j=0;j<i;j++)
            y[i] -= L(i,j) * y[j];

        y[i] /= L(i,i);
    }

    for(int i=n-1;i>=0;i--)
    {
        x[i] = y[i];

        for(int j=i+1;j<n;j++)
            x[i] -= Lt(i,j) * x[j];

        x[i] /= Lt(i,i);
    }

    fout << "\nL Matrix\n";
    L.displayToFile(fout);

    fout << "\nL^T Matrix\n";
    Lt.displayToFile(fout);

    fout << "\nSolution\n";

    for(int i=0;i<n;i++)
        fout << "x" << i+1 << " = " << x[i] << endl;
}