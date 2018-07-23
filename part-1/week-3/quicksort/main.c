#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quicksort.h"
#include "helpers.h"

double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int num = atoi(argv[1]);
    int *array = (int *)malloc(num * sizeof(int));

    // Scanning.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    int *copy1 = (int *)malloc(num * sizeof(int));
    int *copy2 = (int *)malloc(num * sizeof(int));
    int *copy3 = (int *)malloc(num * sizeof(int));
    int *copy4 = (int *)malloc(num * sizeof(int));

    // Copy the elements into 3 different arrays.
    for (int i = 0; i < num; i++)
        copy1[i] = copy2[i] = copy3[i] = copy4[i] = array[i];

    int comparisons1 = 0, comparisons2 = 0, comparisons3 = 0, comparisons4 = 0;
    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_first_element_as_pivot = 0.0;
    double time_last_element_as_pivot= 0.0;
    double time_median_as_pivot = 0.0;
    double time_random_pivot = 0.0;

    // Sort by choosing first element as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(copy1, 0, num - 1, choose_first_element_as_pivot, &comparisons1);
    getrusage(RUSAGE_SELF, &after);
    time_first_element_as_pivot = calculate(&before, &after);

    // Sort by choosing last element as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(copy2, 0, num - 1, choose_last_element_as_pivot, &comparisons2);
    getrusage(RUSAGE_SELF, &after);
    time_last_element_as_pivot = calculate(&before, &after);

    // Sort by choosing the median of first, middle and last elements as the pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(copy3, 0, num - 1, choose_median_as_pivot, &comparisons3);
    getrusage(RUSAGE_SELF, &after);
    time_median_as_pivot = calculate(&before, &after);

    // Sort by choosing a random pivot.
    getrusage(RUSAGE_SELF, &before);
    quicksort(copy4, 0, num - 1, choose_random_pivot, &comparisons4);
    getrusage(RUSAGE_SELF, &after);
    time_random_pivot = calculate(&before, &after);

    // Comparisons.
    printf("Number of comparisons with first element as pivot: %i\n", comparisons1);
    printf("Number of comparisons with last element as pivot:  %i\n", comparisons2);
    printf("Number of comparisons with median as pivot:        %i\n", comparisons3);
    printf("Number of comparisons with a random pivot:         %i\n", comparisons4);

    printf("TIME IN calculating result (first element):        %.2f\n", time_first_element_as_pivot);
    printf("TIME IN calculating result (last element):         %.2f\n", time_last_element_as_pivot);
    printf("TIME IN calculating result (median):               %.2f\n", time_median_as_pivot);
    printf("TIME IN calculating result (random):               %.2f\n", time_random_pivot);
    printf("TIME IN TOTAL:                                     %.2f\n\n",
        time_first_element_as_pivot + time_last_element_as_pivot +
        time_median_as_pivot + time_random_pivot);

    // Cleanup.
    free(array);
    free(copy1);
    free(copy2);
    free(copy3);
    free(copy4);
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

