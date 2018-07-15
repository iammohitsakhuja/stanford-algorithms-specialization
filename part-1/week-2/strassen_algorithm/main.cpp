#include "Matrix.hpp"
#include "strassen.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    Matrix x(n), y(n);
    x.scan();
    y.scan();

    printf("X:\n");
    x.print();
    printf("Y:\n");
    y.print();

    printf("Expected result of X.Y:\n");
    Matrix result = x * y;
    result.print();

    printf("Actual result of X.Y:\n");
    Matrix actual_result = strassen_multiplication(x, y);
    actual_result.print();

    return 0;
}
