#include "Matrix.hpp"

Matrix strassen_multiplication(Matrix &m1, Matrix &m2)
{
    int n = m1.size();

    if (n % 2 == 1)
    {
        Matrix result = m1 * m2;
        return result;
    }

    // Calculate sub matrices.
    Matrix a(n / 2), b(n / 2), c(n / 2), d(n / 2), e(n / 2), f(n / 2), g(n / 2), h(n / 2);

    for (int i = 0, length = n / 2; i < length; i++)
        for (int j = 0; j < length; j++)
        {
            a.matrix[i][j] = m1.matrix[i][j];
            b.matrix[i][j] = m1.matrix[i][n / 2 + j];
            c.matrix[i][j] = m1.matrix[n / 2 + i][j];
            d.matrix[i][j] = m1.matrix[n / 2 + i][n / 2 + j];

            e.matrix[i][j] = m2.matrix[i][j];
            f.matrix[i][j] = m2.matrix[i][n / 2 + j];
            g.matrix[i][j] = m2.matrix[n / 2 + i][j];
            h.matrix[i][j] = m2.matrix[n / 2 + i][n / 2 + j];
        }

    Matrix temp = f - h;
    Matrix p1 = strassen_multiplication(a, temp);

    temp = a + b;
    Matrix p2 = strassen_multiplication(temp, h);

    temp = c + d;
    Matrix p3 = strassen_multiplication(temp, e);

    temp = g - e;
    Matrix p4 = strassen_multiplication(d, temp);

    temp = a + d;
    Matrix temp0 = e + h;
    Matrix p5 = strassen_multiplication(temp, temp0);

    temp = b - d;
    temp0 = g + h;
    Matrix p6 = strassen_multiplication(temp, temp0);

    temp = a - c;
    temp0 = e + f;
    Matrix p7 = strassen_multiplication(temp, temp0);

    Matrix r1 = p5 + p4 - p2 + p6;
    Matrix r2 = p1 + p2;
    Matrix r3 = p3 + p4;
    Matrix r4 = p1 + p5 - p3 - p7;

    Matrix *result = new Matrix(n);

    for (int i = 0, length = n / 2; i < length; i++)
        for (int j = 0; j < length; j++)
        {
            result->matrix[i][j] = r1.matrix[i][j];
            result->matrix[i][n / 2 + j] = r2.matrix[i][j];
            result->matrix[n / 2 + i][j] = r3.matrix[i][j];
            result->matrix[n / 2 + i][n / 2 + j] = r4.matrix[i][j];
        }

    return *result;
}