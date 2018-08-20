#include "helpers.hh"
#include <cstdlib>

/**
 * Swaps two integers.
 */
static void swap(int *a, int *b)
{
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

/**
 * Chooses a random index between [first, last],
 * swaps the element at that index with the first element,
 * and then returns the first element as the pivot.
 */
int choose_random_pivot(int *array, int first, int last)
{
    int n     = last - first + 1;
    int index = first + rand() % n;

    swap(&array[first], &array[index]);

    return array[first];
}

/**
 * Uses the method provided to choose a pivot and then returns it.
 */
int choose_pivot(
    int *array, int first, int last, int (*method)(int *, int, int))
{
    return method(array, first, last);
}

/**
 * Paritions the array around around the pivot such that all elements left to
 * the pivot are less than it, and all elements to right of it are not
 * less than it.
 */
int partition(int *array, int first, int last, int pivot)
{
    // Partition the array around the pivot.
    int wall_index = first;
    for (int i = wall_index + 1; i <= last; i++)
        if (array[i] < pivot)
            swap(&array[++wall_index], &array[i]);

    // Swap the element at the wall with the pivot.
    swap(&array[first], &array[wall_index]);

    return wall_index;
}
