#include "Matrix.hh"
#include <iostream>

Matrix strassen_multiplication(Matrix &m1, Matrix &m2)
{
    // Get the size of the matrices.
    int n = std::min(m1.size(), m2.size());

    // Use simple matrix multiplication if 'n' is odd.
    if (n % 2 == 1 || n <= 100)
        return m1 * m2;

    // Otherwise, create submatrices to divide the bigger matrices into.
    Matrix a(n / 2), b(n / 2), c(n / 2), d(n / 2), e(n / 2), f(n / 2),
        g(n / 2), h(n / 2);

    // Copy the elements from the bigger matrices into the smaller matrices.
    // m1 = [ a b ]             m2 = [ e f ]
    //      [ c d ]                  [ g h ]
    for (int i = 0, length = n / 2; i < length; i++)
        for (int j = 0; j < length; j++) {
            a.matrix[i][j] = m1.matrix[i][j];
            b.matrix[i][j] = m1.matrix[i][n / 2 + j];
            c.matrix[i][j] = m1.matrix[n / 2 + i][j];
            d.matrix[i][j] = m1.matrix[n / 2 + i][n / 2 + j];

            e.matrix[i][j] = m2.matrix[i][j];
            f.matrix[i][j] = m2.matrix[i][n / 2 + j];
            g.matrix[i][j] = m2.matrix[n / 2 + i][j];
            h.matrix[i][j] = m2.matrix[n / 2 + i][n / 2 + j];
        }

    // Calculate the 7 matrices required for Strassen's algorithm.
    // p1 = a * (f - h),
    // p2 = (a + b) * h,
    // p3 = (c + d) * e,
    // p4 = d * (g - e),
    // p5 = (a + d) * (e + h),
    // p6 = (b - d) * (g + h),
    // p7 = (a - c) * (e + f)
    Matrix temp1 = f - h;
    Matrix p1    = strassen_multiplication(a, temp1);

    temp1     = a + b;
    Matrix p2 = strassen_multiplication(temp1, h);

    temp1     = c + d;
    Matrix p3 = strassen_multiplication(temp1, e);

    temp1     = g - e;
    Matrix p4 = strassen_multiplication(d, temp1);

    temp1        = a + d;
    Matrix temp2 = e + h;
    Matrix p5    = strassen_multiplication(temp1, temp2);

    temp1     = b - d;
    temp2     = g + h;
    Matrix p6 = strassen_multiplication(temp1, temp2);

    temp1     = a - c;
    temp2     = e + f;
    Matrix p7 = strassen_multiplication(temp1, temp2);

    // Now, calculate the 4 resulting matrices.
    Matrix r1 = p5 + p4 - p2 + p6;
    Matrix r2 = p1 + p2;
    Matrix r3 = p3 + p4;
    Matrix r4 = p1 + p5 - p3 - p7;

    // Copy the 4 matrices into one resulting matrix.
    // result = [ r1 r2 ]
    //          [ r3 r4 ]
    Matrix *result = new Matrix(n);
    for (int i = 0, length = n / 2; i < length; i++)
        for (int j = 0; j < length; j++) {
            result->matrix[i][j]                 = r1.matrix[i][j];
            result->matrix[i][n / 2 + j]         = r2.matrix[i][j];
            result->matrix[n / 2 + i][j]         = r3.matrix[i][j];
            result->matrix[n / 2 + i][n / 2 + j] = r4.matrix[i][j];
        }

    return *result;
}
