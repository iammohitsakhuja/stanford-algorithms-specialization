#include "helpers.h"

#define UNUSED(x) (void)(x)

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int choose_first_element_as_pivot(int *array, int first, int unused)
{
    UNUSED(unused);
    return array[first];
}

int choose_last_element_as_pivot(int *array, int first, int last)
{
    swap(&array[first], &array[last]);
    return array[first];
}

int choose_median_as_pivot(int *array, int first, int last)
{
    int middle = (first + last) / 2;

    if (array[middle] < array[first])
    {
        if (array[middle] > array[last])
            swap(&array[first], &array[middle]);
        else
            swap(&array[first], &array[last]);
    }
    else
    {
        if (array[middle] == array[first])
            return array[first];
        else
        {
            if (array[middle] <= array[last])
                swap(&array[first], &array[middle]);
            else if (array[last] > array[first])
                swap (&array[first], &array[last]);
        }
    }

    return array[first];
}

int choose_pivot(int *array, int first, int last, int (*method)(int *, int, int))
{
    return method(array, first, last);
}

