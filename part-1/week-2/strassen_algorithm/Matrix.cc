#include "Matrix.hh"
#include <iostream>

// Allocates a n x n matrix.
Matrix::Matrix(int n)
{
    this->n      = n;
    this->matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        this->matrix[i] = (int *)calloc(n, sizeof(int));
}

// Deallocates a n x n matrix.
Matrix::~Matrix(void)
{
    for (int i = 0; i < this->n; i++)
        free(this->matrix[i]);
    free(this->matrix);
}

void Matrix::print(void)
{
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++)
            printf("%9i ", this->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void Matrix::scan(void)
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            scanf("%i", &this->matrix[i][j]);
}

int Matrix::size(void)
{
    return this->n;
}

Matrix Matrix::operator+(Matrix &m)
{
    Matrix result(this->n);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];

    return result;
}

Matrix Matrix::operator-(Matrix &m)
{
    Matrix result(this->n);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            result.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];

    return result;
}

Matrix Matrix::operator*(Matrix &m)
{
    Matrix result(this->n);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < m.n; j++)
            for (int k = 0; k < this->n; k++)
                result.matrix[i][j] += this->matrix[i][k] * m.matrix[k][j];

    return result;
}

bool Matrix::operator==(Matrix &m)
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            if (this->matrix[i][j] != m.matrix[i][j])
                return false;

    return true;
}

void Matrix::operator=(Matrix m)
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            this->matrix[i][j] = m.matrix[i][j];
}
