#include "helpers.h"
#include <stdlib.h>

#define UNUSED(x) (void)(x)

/**
 * Swaps two integers.
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

/**
 * Returns the first element of the array as the pivot.
 */
int choose_first_element_as_pivot(int *array, int first, int unused)
{
    UNUSED(unused);
    return array[first];
}

/**
 * Swaps the first and the last elements, then returns the first as the pivot,
 * hence effective to choosing last element as the pivot.
 */
int choose_last_element_as_pivot(int *array, int first, int last)
{
    swap(&array[first], &array[last]);
    return array[first];
}

/**
 * Chooses a median out of the [first, middle, last] elements,
 * swaps it with the first, and then returns the first element as the pivot.
 */
int choose_median_as_pivot(int *array, int first, int last)
{
    int middle = (first + last) / 2;

    if (array[middle] < array[first]) {
        if (array[middle] >= array[last])
            swap(&array[first], &array[middle]);
        else if (array[last] < array[first])
            swap(&array[first], &array[last]);
    } else if (array[middle] > array[first]) {
        if (array[middle] <= array[last])
            swap(&array[first], &array[middle]);
        else if (array[last] > array[first])
            swap(&array[first], &array[last]);
    }

    return array[first];
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
