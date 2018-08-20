#include "merge_sort.h"
#include <stdlib.h>

void merge_sort(int *array, int first, int last)
{
    if (first == last)
        return;

    int middle = (first + last) / 2;

    // Sort the left array.
    merge_sort(array, first, middle);

    // Sort the right array.
    merge_sort(array, middle + 1, last);

    // Merge the two arrays.
    merge(array, first, middle, last);
}

void merge(int *array, int first, int middle, int last)
{
    // Create 2 new arrays to hold the existing elements.
    int left_len  = middle - first + 1;
    int right_len = last - middle;

    int *left_array  = (int *)malloc(left_len * sizeof(int));
    int *right_array = (int *)malloc(right_len * sizeof(int));

    // Copy the exisiting elements into these 2 arrays.
    for (int i = 0; i < left_len; i++)
        left_array[i] = array[first + i];

    for (int j = 0, length = right_len; j < length; j++)
        right_array[j] = array[middle + 1 + j];

    // Merge the 2 subarrays according to ascending order.
    int i = 0;
    int j = 0;
    int k = first;
    while (i < left_len && j < right_len) {
        if (left_array[i] < right_array[j])
            array[k++] = left_array[i++];
        else
            array[k++] = right_array[j++];
    }

    // Copy over any remaining elements, if any.
    while (i < left_len)
        array[k++] = left_array[i++];

    while (j < right_len)
        array[k++] = right_array[j++];

    // Free the 2 subarrays.
    free(left_array);
    free(right_array);
}
