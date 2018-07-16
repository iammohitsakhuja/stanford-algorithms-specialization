#include "Matrix.hpp"
#include "strassen.hpp"
#include <iostream>

using namespace std;

double calculate(const struct rusage *b, const struct rusage *a);

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

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_proper_method = 0.0, time_strassen_algorithm = 0.0;

    // Expected result.
    getrusage(RUSAGE_SELF, &before);
    Matrix result_by_proper_method = x * y;
    getrusage(RUSAGE_SELF, &after);
    time_proper_method = calculate(&before, &after);

    // Actual result.
    getrusage(RUSAGE_SELF, &before);
    Matrix result_by_strassen_algorithm = strassen_multiplication(x, y);
    getrusage(RUSAGE_SELF, &after);
    time_strassen_algorithm = calculate(&before, &after);

    // Test the correctness.
    result_by_proper_method == result_by_strassen_algorithm ? printf("Equal\n") : printf("Unequal\n");

    printf("TIME IN calculating result by proper method:         %.2f\n", time_proper_method);
    printf("TIME IN calculating result by Strassen's algorithm:  %.2f\n", time_strassen_algorithm);
    printf("TIME IN TOTAL:                                       %.2f\n\n", time_proper_method + time_strassen_algorithm);

    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
