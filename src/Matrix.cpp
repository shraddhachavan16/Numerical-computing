#include "Matrix.h"

// Constructor (using this pointer)
Matrix::Matrix(int r, int c)
{
    this->rows = r;
    this->cols = c;
}

// Copy Constructor
Matrix::Matrix(const Matrix& m)
{
    this->rows = m.rows;
    this->cols = m.cols;

    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            this->mat[i][j] = m.mat[i][j];
}

// Read Matrix
void Matrix::read()
{
    cout << "Enter elements:\n";

    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            cin >> this->mat[i][j];
}

// Display Matrix
void Matrix::display() const
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
            cout << this->mat[i][j] << " ";

        cout << endl;
    }
}

// Addition
Matrix Matrix::add(const Matrix& m)
{
    if(this->rows != m.rows || this->cols != m.cols)
        throw "Addition not possible";

    Matrix result(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            result.mat[i][j] =
                this->mat[i][j] + m.mat[i][j];

    return result;
}

// Subtraction
Matrix Matrix::sub(const Matrix& m)
{
    if(this->rows != m.rows || this->cols != m.cols)
        throw "Subtraction not possible";

    Matrix result(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            result.mat[i][j] =
                this->mat[i][j] - m.mat[i][j];

    return result;
}

// Gaussian Elimination (WITHOUT Pivoting)
void Matrix::gaussianElimination()
{
    if(this->rows + 1 != this->cols)
        throw "Use augmented matrix (n x n+1)";

    int n = this->rows;

    for(int k = 0; k < n - 1; k++)
    {
        // Check pivot (no swapping)
        if(this->mat[k][k] == 0)
        {
            cout << "\nZero pivot found. Cannot proceed.\n";
            return;
        }

        for(int i = k + 1; i < n; i++)
        {
            float factor =
                this->mat[i][k] / this->mat[k][k];

            for(int j = k; j < this->cols; j++)
            {
                this->mat[i][j] -=
                    factor * this->mat[k][j];
            }
        }
    }

    cout << "\nUpper Triangular Matrix:\n";
    this->display();

    this->backSubstitution();
}

// Back Substitution
void Matrix::backSubstitution()
{
    int n = this->rows;
    float x[10];

    for(int i = n - 1; i >= 0; i--)
    {
        if(this->mat[i][i] == 0)
        {
            cout << "\nNo unique solution.\n";
            return;
        }

        x[i] = this->mat[i][this->cols - 1];

        for(int j = i + 1; j < n; j++)
            x[i] -= this->mat[i][j] * x[j];

        x[i] = x[i] / this->mat[i][i];
    }

    cout << "\nSolution:\n";

    for(int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << x[i] << endl;
}