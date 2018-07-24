#include <cstdlib>
#include "helpers.hpp"

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int choose_random_pivot(int *array, int first, int last)
{
    int n = last - first + 1;
    int index = first + rand() % n;

    swap(&array[first], &array[index]);

    return array[first];
}

int choose_pivot(int *array, int first, int last, int (*method)(int *, int, int))
{
    return method(array, first, last);
}

int partition(int *array, int first, int last, int pivot)
{
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

    return wall_index;
}

