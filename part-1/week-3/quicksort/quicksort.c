#include "quicksort.h"
#include "helpers.h"
#include <stdio.h>

void quicksort(int *array, int first, int last, int (*method)(int *, int, int), int *comparisons)
{
    int n = last - first + 1;
    if (n <= 1)
    {
        return;
    }

    int pivot = choose_pivot(array, first, last, method);
    int wall_index = partition(array, first, last, pivot);
    *comparisons += last - first;

    // Sort the left and right subarrays.
    quicksort(array, first, wall_index - 1, method, comparisons);
    quicksort(array, wall_index + 1, last, method, comparisons);
}

