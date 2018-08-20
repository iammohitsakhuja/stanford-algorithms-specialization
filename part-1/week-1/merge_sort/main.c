#include "benchmark.h"
#include "merge_sort.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void test(int *array, int length);
bool is_sorted(int *array, int length);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Create an array.
    int length = atoi(argv[1]);
    int *array = (int *)malloc(length * sizeof(int));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_to_sort = 0.0;

    // Input.
    for (int i = 0; i < length; i++)
        scanf("%i", &array[i]);

    // Sort and benchmark the results.
    getrusage(RUSAGE_SELF, &before);
    merge_sort(array, 0, length - 1);
    getrusage(RUSAGE_SELF, &after);
    time_to_sort = calculate(&before, &after);

    // Display the benchmark results.
    printf("TIME in sorting: %lf\n", time_to_sort);

    // Run tests.
    test(array, length);
    printf("All tests passed!\n");

    // Housekeeping.
    free(array);
    return 0;
}

void test(int *array, int length)
{
    // Check if the array is sorted.
    assert(is_sorted(array, length));
}

bool is_sorted(int *array, int length)
{
    for (int i = 0; i < length - 1; i++)
        if (array[i] > array[i + 1])
            return false;

    return true;
}
