#include "rselect.hh"
#include "helpers.hh"

int rselect(
    int *array, int first, int last, int order, int (*method)(int *, int, int))
{
    // Get the total number of elements in the array.
    // If there is only 1 element, then that is the order.
    int n = last - first + 1;
    if (n <= 1)
        return array[first];

    // Choose a pivot by using the specified method.
    int pivot = choose_pivot(array, first, last, method);

    // Partition the array into 2 according to the chosen pivot.
    int wall_index = partition(array, first, last, pivot);

    // If the wall index is equal to the order, then that is the element.
    if (wall_index == order)
        return array[wall_index];
    // Else, recurse on the appropriate subarray to find the element.
    else if (wall_index > order)
        return rselect(array, first, wall_index - 1, order, method);
    else
        return rselect(array, wall_index + 1, last, order, method);
}
