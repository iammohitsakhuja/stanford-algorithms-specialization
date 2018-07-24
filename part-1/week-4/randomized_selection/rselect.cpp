#include "rselect.hpp"
#include "helpers.hpp"

int rselect(int *array, int first, int last, int order, int (*method)(int *, int, int))
{
    int n = last - first + 1;
    if (n <= 1)
        return array[first];

    int pivot = choose_pivot(array, first, last, method);
    int wall_index = partition(array, first, last, pivot);

    if (wall_index == order)
        return array[wall_index];
    else if (wall_index > order)
        return rselect(array, first, wall_index - 1, order, method);
    else
        return rselect(array, wall_index + 1, last, order, method);
}

