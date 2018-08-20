#include "benchmark.h"
#include "helpers.h"
#include "merge_sort.h"
#include "quicksort.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test(int *array, int length);
bool is_sorted(int *array, int length);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Use current system time as a seed for generating random numbers.
    srand(time(NULL));

    // Create an array of the specified size.
    int num    = atoi(argv[1]);
    int *array = (int *)malloc(num * sizeof(int));

    // Create 5 arrays for copying the array into,
    // needed for applying the 4 different methods of choosing a pivot,
    // and for sorting via merge sort.
    int *first_element_as_pivot = (int *)malloc(num * sizeof(int));
    int *last_element_as_pivot  = (int *)malloc(num * sizeof(int));
    int *median_as_pivot        = (int *)malloc(num * sizeof(int));
    int *random_pivot           = (int *)malloc(num * sizeof(int));
    int *merge_sort_array       = (int *)malloc(num * sizeof(int));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_first_element_as_pivot = 0.0;
    double time_last_element_as_pivot  = 0.0;
    double time_median_as_pivot        = 0.0;
    double time_random_pivot           = 0.0;
    double time_merge_sort             = 0.0;

    // Comparisons.
    int comparisons_first_element_as_pivot = 0;
    int comparisons_last_element_as_pivot  = 0;
    int comparisons_median_as_pivot        = 0;
    int comparisons_random_pivot           = 0;

    // Input the array.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    // Copy the array elements into 5 different arrays.
    for (int i = 0; i < num; i++)
        first_element_as_pivot[i] = last_element_as_pivot[i]
            = median_as_pivot[i] = random_pivot[i] = merge_sort_array[i]
            = array[i];

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

    // Benchmark the time taken to sort by choosing a random pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(random_pivot, 0, num - 1, choose_random_pivot,
        &comparisons_random_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_random_pivot = calculate(&before, &after);

    // Benchmark the time taken to sort via merge sort.
    getrusage(RUSAGE_SELF, &before);
    merge_sort(merge_sort_array, 0, num - 1);
    getrusage(RUSAGE_SELF, &after);
    time_merge_sort = calculate(&before, &after);

    // Display comparisons.
    printf("Number of comparisons with first element as pivot: %i\n",
        comparisons_first_element_as_pivot);
    printf("Number of comparisons with last element as pivot:  %i\n",
        comparisons_last_element_as_pivot);
    printf("Number of comparisons with median as pivot:        %i\n",
        comparisons_median_as_pivot);
    printf("Number of comparisons with a random pivot:         %i\n\n",
        comparisons_random_pivot);

    // Display the benchmark results.
    printf("TIME IN sorting (first element):  %6.2f\n",
        time_first_element_as_pivot);
    printf("TIME IN sorting (last element):   %6.2f\n",
        time_last_element_as_pivot);
    printf("TIME IN sorting (median):         %6.2f\n", time_median_as_pivot);
    printf("TIME IN sorting (random):         %6.2f\n", time_random_pivot);
    printf("TIME IN sorting (merge sort):     %6.2f\n", time_merge_sort);
    printf("TIME IN TOTAL:                    %6.2f\n",
        time_first_element_as_pivot + time_last_element_as_pivot
            + time_median_as_pivot + time_random_pivot + time_merge_sort);

    // Run all tests.
    test(first_element_as_pivot, num);
    test(last_element_as_pivot, num);
    test(median_as_pivot, num);
    test(random_pivot, num);
    test(merge_sort_array, num);
    printf("\nAll tests passed!\n");

    // Housekeeping.
    free(first_element_as_pivot);
    free(last_element_as_pivot);
    free(median_as_pivot);
    free(random_pivot);
    free(merge_sort_array);
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
