#include "quicksort.h"
#include "helpers.h"

void quicksort(int *array, int first, int last, int (*method)(int *, int, int),
    int *comparisons)
{
    // Get the total number of elements in the array.
    // If there is only 1 element, then it is already sorted.
    int n = last - first + 1;
    if (n <= 1)
        return;

    // Choose a pivot by using the specified method.
    int pivot = choose_pivot(array, first, last, method);

    // Partition the array into 2 according to the chosen pivot.
    int wall_index = partition(array, first, last, pivot);

    // Count the total number of comparisons made while partitioning.
    *comparisons += last - first;

    // Sort the left and right subarrays.
    quicksort(array, first, wall_index - 1, method, comparisons);
    quicksort(array, wall_index + 1, last, method, comparisons);
}
