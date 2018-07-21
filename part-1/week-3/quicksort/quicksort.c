#include "quicksort.h"
#include "helpers.h"
#include <stdio.h>

void quicksort(int *array, int first, int last, int (*method)(int *, int, int))
{
    int n = last - first + 1;
    if (n <= 1)
    {
        return;
    }

    int pivot = choose_pivot(array, first, last, method);
    int wall_index = first;
    for (int i = wall_index + 1; i <= last; i++)
    {
        if (array[i] < pivot)
        {
            wall_index++;
            swap(&array[wall_index], &array[i]);
        }
    }

    // Swap the element at the wall with the pivot.
    swap(&array[first], &array[wall_index]);

    // Sort the left and right subarrays.
    quicksort(array, first, wall_index - 1, method);
    quicksort(array, wall_index + 1, last, method);
}

