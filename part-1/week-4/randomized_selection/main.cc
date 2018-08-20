#include "benchmark.hh"
#include "helpers.hh"
#include "quicksort.hh"
#include "rselect.hh"
#include <iostream>

using namespace std;

void test(int num1, int num2);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 3) {
        printf("Usage: %s num order\n", argv[0]);
        return 1;
    }

    // Use current system time as a seed for generating random numbers.
    srand(time(NULL));

    // Create an array of the specified size.
    int num    = atoi(argv[1]);
    int order  = atoi(argv[2]);
    int *array = (int *)malloc(num * sizeof(int));

    // Create 2 copies of the array:
    // One for directly searching into - via randomized selection,
    // Other for first sorting the array and then finding the number.
    int *rselect_array = (int *)malloc(num * sizeof(int));
    int *qsort_array   = (int *)malloc(num * sizeof(int));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_randomized_selection = 0.0;
    double time_quicksort            = 0.0;

    // Input the array.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    // Copy the array elements into the other 2 arrays.
    for (int i = 0; i < num; i++)
        rselect_array[i] = qsort_array[i] = array[i];

    // Benchmark the time taken to find the element using randomized selection.
    getrusage(RUSAGE_SELF, &before);
    int element
        = rselect(rselect_array, 0, num - 1, order, choose_random_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_randomized_selection = calculate(&before, &after);

    // Benchmark the time taken to find the element after sorting the array.
    getrusage(RUSAGE_SELF, &before);
    quicksort(qsort_array, 0, num - 1, choose_random_pivot);
    getrusage(RUSAGE_SELF, &after);
    time_quicksort = calculate(&before, &after);

    // Display the benchmark results.
    printf("TIME IN finding the element (randomized selection): %.2f\n",
        time_randomized_selection);
    printf("TIME IN finding the element (quicksort):            %.2f\n",
        time_quicksort);

    // Run all tests.
    test(element, qsort_array[order]);
    printf("\nAll tests passed!\n");

    // Housekeeping.
    free(rselect_array);
    free(qsort_array);
    free(array);
    return 0;
}

void test(int num1, int num2)
{
    assert(num1 == num2);
}
