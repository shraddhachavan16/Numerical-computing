// // #include "Matrix.h"

// // // Constructor (using this pointer)
// // Matrix::Matrix(int r, int c)
// // {
// //     this->rows = r;
// //     this->cols = c;
// // }

// // // Copy Constructor
// // Matrix::Matrix(const Matrix& m)
// // {
// //     this->rows = m.rows;
// //     this->cols = m.cols;

// //     for(int i = 0; i < this->rows; i++)
// //         for(int j = 0; j < this->cols; j++)
// //             this->mat[i][j] = m.mat[i][j];
// // }

// // // Read Matrix
// // void Matrix::read()
// // {
// //     cout << "Enter elements:\n";

// //     for(int i = 0; i < this->rows; i++)
// //         for(int j = 0; j < this->cols; j++)
// //             cin >> this->mat[i][j];
// // }

// // // Display Matrix
// // void Matrix::display() const
// // {
// //     for(int i = 0; i < this->rows; i++)
// //     {
// //         for(int j = 0; j < this->cols; j++)
// //             cout << this->mat[i][j] << " ";

// //         cout << endl;
// //     }
// // }

// // // Addition
// // Matrix Matrix::add(const Matrix& m)
// // {
// //     if(this->rows != m.rows || this->cols != m.cols)
// //         throw "Addition not possible";

// //     Matrix result(this->rows, this->cols);

// //     for(int i = 0; i < this->rows; i++)
// //         for(int j = 0; j < this->cols; j++)
// //             result.mat[i][j] =
// //                 this->mat[i][j] + m.mat[i][j];

// //     return result;
// // }

// // // Subtraction
// // Matrix Matrix::sub(const Matrix& m)
// // {
// //     if(this->rows != m.rows || this->cols != m.cols)
// //         throw "Subtraction not possible";

// //     Matrix result(this->rows, this->cols);

// //     for(int i = 0; i < this->rows; i++)
// //         for(int j = 0; j < this->cols; j++)
// //             result.mat[i][j] =
// //                 this->mat[i][j] - m.mat[i][j];

// //     return result;
// // }

// // // Gaussian Elimination (WITHOUT Pivoting)
// // void Matrix::gaussianElimination()
// // {
// //     if(this->rows + 1 != this->cols)
// //         throw "Use augmented matrix (n x n+1)";

// //     int n = this->rows;

// //     for(int k = 0; k < n - 1; k++)
// //     {
// //         // Check pivot (no swapping)
// //         if(this->mat[k][k] == 0)
// //         {
// //             cout << "\nZero pivot found. Cannot proceed.\n";
// //             return;
// //         }

// //         for(int i = k + 1; i < n; i++)
// //         {
// //             float factor =
// //                 this->mat[i][k] / this->mat[k][k];

// //             for(int j = k; j < this->cols; j++)
// //             {
// //                 this->mat[i][j] -=
// //                     factor * this->mat[k][j];
// //             }
// //         }
// //     }

// //     cout << "\nUpper Triangular Matrix:\n";
// //     this->display();

// //     this->backSubstitution();
// // }

// // // Back Substitution
// // void Matrix::backSubstitution()
// // {
// //     int n = this->rows;
// //     float x[10];

// //     for(int i = n - 1; i >= 0; i--)
// //     {
// //         if(this->mat[i][i] == 0)
// //         {
// //             cout << "\nNo unique solution.\n";
// //             return;
// //         }

// //         x[i] = this->mat[i][this->cols - 1];

// //         for(int j = i + 1; j < n; j++)
// //             x[i] -= this->mat[i][j] * x[j];

// //         x[i] = x[i] / this->mat[i][i];
// //     }

// //     cout << "\nSolution:\n";

// //     for(int i = 0; i < n; i++)
// //         cout << "x" << i + 1 << " = " << x[i] << endl;
// // }

// #include "Matrix.h"
// #include <cmath>

// Matrix::Matrix(){}

// Matrix::Matrix(int r,int c)
// {
//     rows=r;
//     cols=c;
//     data.assign(r,vector<double>(c,0));
// }

// Matrix::Matrix(const Matrix &m)
// {
//     rows=m.rows;
//     cols=m.cols;
//     data=m.data;
// }

// // void Matrix::readFromFile(ifstream &fin)
// // {
// //     fin>>rows>>cols;
// //     data.assign(rows,vector<double>(cols));

// //     for(int i=0;i<rows;i++)
// //         for(int j=0;j<cols;j++)
// //             fin>>data[i][j];
// // }

// void Matrix::readFromFile(ifstream &fin)
// {
//     fin >> rows >> cols;

//     data.assign(rows, vector<double>(cols));

//     for(int i=0;i<rows;i++)
//     {
//         for(int j=0;j<cols;j++)
//         {
//             if(!(fin >> data[i][j]))
//             {
//                 cout << "Input file error at row "
//                      << i+1 << " column " << j+1 << endl;
//                 exit(1);
//             }
//         }
//     }
// }

// void Matrix::displayToFile(ofstream &fout) const
// {
//     for(int i=0;i<rows;i++)
//     {
//         for(int j=0;j<cols;j++)
//             fout<<data[i][j]<<" ";
//         fout<<"\n";
//     }
// }

// double &Matrix::operator()(int i,int j)
// {
//     return data[i][j];
// }

// double Matrix::operator()(int i,int j) const
// {
//     return data[i][j];
// }

// Matrix Matrix::operator+(const Matrix &m) const
// {
//     Matrix r(rows,cols);
//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             r.data[i][j]=data[i][j]+m.data[i][j];
//     return r;
// }

// Matrix Matrix::operator-(const Matrix &m) const
// {
//     Matrix r(rows,cols);
//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             r.data[i][j]=data[i][j]-m.data[i][j];
//     return r;
// }

// Matrix Matrix::operator*(const Matrix &m) const
// {
//     Matrix r(rows,m.cols);

//     for(int i=0;i<rows;i++)
//         for(int j=0;j<m.cols;j++)
//             for(int k=0;k<cols;k++)
//                 r.data[i][j]+=data[i][k]*m.data[k][j];

//     return r;
// }

// bool Matrix::operator==(const Matrix &m) const
// {
//     if(rows!=m.rows || cols!=m.cols) return false;

//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             if(data[i][j]!=m.data[i][j])
//                 return false;

//     return true;
// }

// istream &operator>>(istream &in, Matrix &m)
// {
//     for(int i=0;i<m.rows;i++)
//         for(int j=0;j<m.cols;j++)
//             in>>m.data[i][j];
//     return in;
// }

// ostream &operator<<(ostream &out,const Matrix &m)
// {
//     for(int i=0;i<m.rows;i++)
//     {
//         for(int j=0;j<m.cols;j++)
//             out<<m.data[i][j]<<" ";
//         out<<"\n";
//     }
//     return out;
// }

// bool Matrix::isSquare() const
// {
//     return rows==cols;
// }

// bool Matrix::isNull() const
// {
//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             if(data[i][j]!=0)
//                 return false;

//     return true;
// }

// bool Matrix::isDiagonal() const
// {
//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             if(i!=j && data[i][j]!=0)
//                 return false;

//     return true;
// }

// bool Matrix::isIdentity() const
// {
//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//         {
//             if(i==j && data[i][j]!=1) return false;
//             if(i!=j && data[i][j]!=0) return false;
//         }

//     return true;
// }

// Matrix Matrix::transpose() const
// {
//     Matrix t(cols,rows);

//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             t.data[j][i]=data[i][j];

//     return t;
// }

// bool Matrix::isSymmetric() const
// {
//     if(!isSquare()) return false;

//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             if(data[i][j]!=data[j][i])
//                 return false;

//     return true;
// }

// bool Matrix::isDiagonallyDominant() const
// {
//     for(int i=0;i<rows;i++)
//     {
//         double sum=0;

//         for(int j=0;j<cols;j++)
//             if(i!=j)
//                 sum+=fabs(data[i][j]);

//         if(fabs(data[i][i])<sum)
//             return false;
//     }

//     return true;
// }

// bool Matrix::isTranspose(const Matrix &m) const
// {
//     if(rows!=m.cols || cols!=m.rows)
//         return false;

//     for(int i=0;i<rows;i++)
//         for(int j=0;j<cols;j++)
//             if(data[i][j]!=m.data[j][i])
//                 return false;

//     return true;
// }

// void Matrix::makeDiagonallyDominant(){}

// // double Matrix::determinant() const
// // {
// //     return 0;
// // }

// // Matrix Matrix::inverse() const
// // {
// //     return Matrix();
// // }

// double Matrix::determinant() const
// {
//     if(rows != cols)
//     {
//         cout << "Determinant only for square matrix\n";
//         return 0;
//     }

//     Matrix temp(*this); 
//     double det = 1;

//     for(int k = 0; k < rows; k++)
//     {
//         if(fabs(temp.data[k][k]) < 1e-12)
//             return 0;

//         for(int i = k + 1; i < rows; i++)
//         {
//             double factor = temp.data[i][k] / temp.data[k][k];

//             for(int j = k; j < cols; j++)
//             {
//                 temp.data[i][j] -= factor * temp.data[k][j];
//             }
//         }
//     }

//     for(int i = 0; i < rows; i++)
//         det *= temp.data[i][i];

//     return det;
// }
// Matrix Matrix::inverse() const
// {
//     if(rows != cols)
//     {
//         cout<<"Inverse only for square matrix\n";
//         return Matrix();
//     }

//     int n = rows;
//     Matrix aug(n, 2*n);

//     for(int i=0;i<n;i++)
//     {
//         for(int j=0;j<n;j++)
//             aug(i,j) = (*this)(i,j);

//         for(int j=0;j<n;j++)
//             aug(i,j+n) = (i==j)?1:0;
//     }

//     for(int i=0;i<n;i++)
//     {
//         double pivot = aug(i,i);

//         if(fabs(pivot) < 1e-12)
//         {
//             cout<<"Matrix not invertible\n";
//             return Matrix();
//         }

//         for(int j=0;j<2*n;j++)
//             aug(i,j) /= pivot;

//         for(int k=0;k<n;k++)
//         {
//             if(k==i) continue;

//             double factor = aug(k,i);

//             for(int j=0;j<2*n;j++)
//                 aug(k,j) -= factor * aug(i,j);
//         }
//     }

//     Matrix inv(n,n);

//     for(int i=0;i<n;i++)
//         for(int j=0;j<n;j++)
//             inv(i,j) = aug(i,j+n);

//     return inv;


//     #include <cmath>

// void Matrix::gershgorinDiscs(ofstream &fout) const
// {
//     if(!isSquare())
//     {
//         fout << "Gershgorin theorem applies only to square matrices\n";
//         return;
//     }

//     fout << "\n===== Gershgorin Discs =====\n";

//     for(int i = 0; i < rows; i++)
//     {
//         double center = data[i][i];
//         double radius = 0;

//         for(int j = 0; j < cols; j++)
//         {
//             if(i != j)
//                 radius += fabs(data[i][j]);
//         }

//         fout << "Disc " << i+1 << ":\n";
//         fout << "Center = " << center << "\n";
//         fout << "Radius = " << radius << "\n";
//         fout << "Range = ["
//              << center - radius << ", "
//              << center + radius << "]\n\n";
//     }

//     fout << "All eigenvalues lie within these discs.\n";

//     // 🔥 BONUS
//     if(isDiagonallyDominant())
//         fout << "Matrix is diagonally dominant → good for iterative methods\n";
// }
    
#include "Matrix.h"
#include <cmath>
#include <iostream>

using namespace std;

// ===============================
// CONSTRUCTORS
// ===============================
Matrix::Matrix(){}

Matrix::Matrix(int r,int c)
{
    rows=r;
    cols=c;
    data.assign(r,vector<double>(c,0));
}

Matrix::Matrix(const Matrix &m)
{
    rows=m.rows;
    cols=m.cols;
    data=m.data;
}

// ===============================
// FILE INPUT
// ===============================
void Matrix::readFromFile(ifstream &fin)
{
    fin >> rows >> cols;

    data.assign(rows, vector<double>(cols));

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(!(fin >> data[i][j]))
            {
                cout << "Input file error at row "
                     << i+1 << " column " << j+1 << endl;
                exit(1);
            }
        }
    }
}

// ===============================
// DISPLAY
// ===============================
void Matrix::displayToFile(ofstream &fout) const
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            fout<<data[i][j]<<" ";
        fout<<"\n";
    }
}

// ===============================
// OPERATORS
// ===============================
double &Matrix::operator()(int i,int j)
{
    return data[i][j];
}

double Matrix::operator()(int i,int j) const
{
    return data[i][j];
}

Matrix Matrix::operator+(const Matrix &m) const
{
    Matrix r(rows,cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            r.data[i][j]=data[i][j]+m.data[i][j];
    return r;
}

Matrix Matrix::operator-(const Matrix &m) const
{
    Matrix r(rows,cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            r.data[i][j]=data[i][j]-m.data[i][j];
    return r;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    Matrix r(rows,m.cols);

    for(int i=0;i<rows;i++)
        for(int j=0;j<m.cols;j++)
            for(int k=0;k<cols;k++)
                r.data[i][j]+=data[i][k]*m.data[k][j];

    return r;
}

// ===============================
// MATRIX PROPERTIES
// ===============================
bool Matrix::isSquare() const
{
    return rows==cols;
}

bool Matrix::isDiagonal() const
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(i!=j && data[i][j]!=0)
                return false;

    return true;
}

bool Matrix::isIdentity() const
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            if(i==j && data[i][j]!=1) return false;
            if(i!=j && data[i][j]!=0) return false;
        }

    return true;
}

bool Matrix::isNull() const
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(data[i][j]!=0)
                return false;

    return true;
}

bool Matrix::isSymmetric() const
{
    if(!isSquare()) return false;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(data[i][j]!=data[j][i])
                return false;

    return true;
}

bool Matrix::isDiagonallyDominant() const
{
    for(int i=0;i<rows;i++)
    {
        double sum=0;

        for(int j=0;j<cols;j++)
            if(i!=j)
                sum+=fabs(data[i][j]);

        if(fabs(data[i][i])<sum)
            return false;
    }

    return true;
}

// ===============================
// TRANSPOSE
// ===============================
Matrix Matrix::transpose() const
{
    Matrix t(cols,rows);

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            t.data[j][i]=data[i][j];

    return t;
}

// ===============================
// DETERMINANT
// ===============================
double Matrix::determinant() const
{
    if(rows != cols)
    {
        cout << "Determinant only for square matrix\n";
        return 0;
    }

    Matrix temp(*this); 
    double det = 1;

    for(int k = 0; k < rows; k++)
    {
        if(fabs(temp.data[k][k]) < 1e-12)
            return 0;

        for(int i = k + 1; i < rows; i++)
        {
            double factor = temp.data[i][k] / temp.data[k][k];

            for(int j = k; j < cols; j++)
                temp.data[i][j] -= factor * temp.data[k][j];
        }
    }

    for(int i = 0; i < rows; i++)
        det *= temp.data[i][i];

    return det;
}

// ===============================
// INVERSE (GAUSS-JORDAN)
// ===============================
Matrix Matrix::inverse() const
{
    if(rows != cols)
    {
        cout<<"Inverse only for square matrix\n";
        return Matrix();
    }

    int n = rows;
    Matrix aug(n, 2*n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            aug(i,j) = (*this)(i,j);

        for(int j=0;j<n;j++)
            aug(i,j+n) = (i==j)?1:0;
    }

    for(int i=0;i<n;i++)
    {
        double pivot = aug(i,i);

        if(fabs(pivot) < 1e-12)
        {
            cout<<"Matrix not invertible\n";
            return Matrix();
        }

        for(int j=0;j<2*n;j++)
            aug(i,j) /= pivot;

        for(int k=0;k<n;k++)
        {
            if(k==i) continue;

            double factor = aug(k,i);

            for(int j=0;j<2*n;j++)
                aug(k,j) -= factor * aug(i,j);
        }
    }

    Matrix inv(n,n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            inv(i,j) = aug(i,j+n);

    return inv;
}

// ===============================
// GERSHGORIN THEOREM
// ===============================
void Matrix::gershgorinDiscs(ofstream &fout) const
{
    if(!isSquare())
    {
        fout << "Gershgorin theorem applies only to square matrices\n";
        return;
    }

    fout << "\n===== Gershgorin Discs =====\n";

    for(int i = 0; i < rows; i++)
    {
        double center = data[i][i];
        double radius = 0;

        for(int j = 0; j < cols; j++)
        {
            if(i != j)
                radius += fabs(data[i][j]);
        }

        fout << "Disc " << i+1 << ":\n";
        fout << "Center = " << center << "\n";
        fout << "Radius = " << radius << "\n";
        fout << "Range = ["
             << center - radius << ", "
             << center + radius << "]\n\n";
    }

    fout << "All eigenvalues lie within these discs.\n";

    if(isDiagonallyDominant())
        fout << "Matrix is diagonally dominant → good for iterative methods\n";
}
ostream &operator<<(ostream &out, const Matrix &m)
{
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.cols; j++)
        {
            out << m.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
Matrix Matrix::getCoefficientMatrix() const
{
    Matrix m(rows, cols - 1);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols - 1; j++)
            m(i,j) = data[i][j];

    return m;
}

