#include "Matrix.hh"
#include "benchmark.hh"
#include "strassen.hh"
#include <iostream>

using namespace std;

void test(
    Matrix &result_by_proper_method, Matrix &result_by_strassen_algorithm);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Create 2 n x n matrices.
    int n = atoi(argv[1]);
    Matrix x(n), y(n);

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_proper_method = 0.0, time_strassen_algorithm = 0.0;

    // Input.
    x.scan();
    y.scan();

    // Benchmark the time taken in multiplying matrices by using the
    // proper matrix multiplication method.
    getrusage(RUSAGE_SELF, &before);
    Matrix result_by_proper_method = x * y;
    getrusage(RUSAGE_SELF, &after);
    time_proper_method = calculate(&before, &after);

    // Benchmark the time taken in multiplying matrices by using Strassen's
    // algorithm.
    getrusage(RUSAGE_SELF, &before);
    Matrix result_by_strassen_algorithm = strassen_multiplication(x, y);
    getrusage(RUSAGE_SELF, &after);
    time_strassen_algorithm = calculate(&before, &after);

    // Display the benchmark results.
    printf("TIME IN calculating result by proper method:         %.2f\n",
        time_proper_method);
    printf("TIME IN calculating result by Strassen's algorithm:  %.2f\n",
        time_strassen_algorithm);
    printf("TIME IN TOTAL:                                       %.2f\n\n",
        time_proper_method + time_strassen_algorithm);

    // Run all tests.
    test(result_by_proper_method, result_by_strassen_algorithm);
    printf("All tests passed!\n");

    return 0;
}

void test(
    Matrix &result_by_proper_method, Matrix &result_by_strassen_algorithm)
{
    assert(result_by_proper_method == result_by_strassen_algorithm);
}
