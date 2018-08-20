#include "benchmark.h"
#include "counting_inversions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Create an array to hold the values.
    int length = atoi(argv[1]);
    int *array = (int *)malloc(length * sizeof(int));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_sort_and_count = 0.0;

    // Input.
    for (int i = 0; i < length; i++)
        scanf("%i", &array[i]);

    // Sort the array and count the number of inversions in it.
    getrusage(RUSAGE_SELF, &before);
    long long int inversions = sort_and_count(array, 0, length - 1);
    getrusage(RUSAGE_SELF, &after);
    time_sort_and_count = calculate(&before, &after);

    // Display the results.
    printf("Number of inversions = %lld\n", inversions);

    // Display the benchmark results.
    printf("TIME IN sorting the array and counting inversions: %lf\n",
        time_sort_and_count);

    // Housekeeping.
    free(array);
    return 0;
}
