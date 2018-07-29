#include <assert.h>
#include "benchmark.h"
#include "helpers.h"
#include "quicksort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test(int *array, int length);
bool is_sorted(int *array, int length);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Use current system time as a seed for generating random numbers.
    srand(time(NULL));

    // Create an array of the specified size.
    int num = atoi(argv[1]);
    int *array = (int *)malloc(num * sizeof(int));

    // Create 4 arrays for copying the array into,
    // needed for applying the 4 different methods of choosing a pivot.
    int *first_element_as_pivot = (int *)malloc(num * sizeof(int));
    int *last_element_as_pivot  = (int *)malloc(num * sizeof(int));
    int *median_as_pivot        = (int *)malloc(num * sizeof(int));
    int *random_pivot           = (int *)malloc(num * sizeof(int));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_first_element_as_pivot = 0.0;
    double time_last_element_as_pivot  = 0.0;
    double time_median_as_pivot        = 0.0;
    double time_random_pivot           = 0.0;

    // Comparisons.
    int comparisons_first_element_as_pivot = 0;
    int comparisons_last_element_as_pivot  = 0;
    int comparisons_median_as_pivot        = 0;
    int comparisons_random_pivot           = 0;

    // Input the array.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    // Copy the array elements into 4 different arrays.
    for (int i = 0; i < num; i++)
        first_element_as_pivot[i] = last_element_as_pivot[i] =
            median_as_pivot[i] = random_pivot[i] = array[i];

    // Benchmark the time taken to sort by choosing first element as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(first_element_as_pivot, 0, num - 1,
        choose_first_element_as_pivot, &comparisons_first_element_as_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_first_element_as_pivot = calculate(&before, &after);

    // Benchmark the time taken to sort by choosing last element as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(last_element_as_pivot, 0, num - 1, choose_last_element_as_pivot,
        &comparisons_last_element_as_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_last_element_as_pivot = calculate(&before, &after);

    // Benchmark the time taken to sort by choosing the median of first,
    // middle and last elements as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(median_as_pivot, 0, num - 1, choose_median_as_pivot,
        &comparisons_median_as_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_median_as_pivot = calculate(&before, &after);

    // Benchmark the time taken sort by choosing a random pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(random_pivot, 0, num - 1, choose_random_pivot,
        &comparisons_random_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_random_pivot = calculate(&before, &after);

    // Display comparisons.
    printf("Number of comparisons with first element as pivot: %i\n",
        comparisons_first_element_as_pivot);
    printf("Number of comparisons with last element as pivot:  %i\n",
        comparisons_last_element_as_pivot);
    printf("Number of comparisons with median as pivot:        %i\n",
        comparisons_median_as_pivot);
    printf("Number of comparisons with a random pivot:         %i\n",
        comparisons_random_pivot);

    // Display the benchmark results.
    printf("TIME IN calculating result (first element):        %.2f\n",
        time_first_element_as_pivot);
    printf("TIME IN calculating result (last element):         %.2f\n",
        time_last_element_as_pivot);
    printf("TIME IN calculating result (median):               %.2f\n",
        time_median_as_pivot);
    printf("TIME IN calculating result (random):               %.2f\n",
        time_random_pivot);
    printf("TIME IN TOTAL:                                     %.2f\n",
        time_first_element_as_pivot + time_last_element_as_pivot +
        time_median_as_pivot + time_random_pivot);

    // Run all tests.
    test(first_element_as_pivot, num);
    test(last_element_as_pivot, num);
    test(median_as_pivot, num);
    test(random_pivot, num);
    printf("\nAll tests passed!\n");

    // Housekeeping.
    free(first_element_as_pivot);
    free(last_element_as_pivot);
    free(median_as_pivot);
    free(random_pivot);
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

