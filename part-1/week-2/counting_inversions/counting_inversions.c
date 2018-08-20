#include "counting_inversions.h"
#include <stdlib.h>

long long int sort_and_count(int *array, int first, int last)
{
    if (first == last)
        return 0;
    else /* Return 0 if there is only 1 element. */
    {
        int middle = (first + last) / 2;

        // Count the number of inversions in the left subarray.
        long long int left_inversions = sort_and_count(array, first, middle);

        // Count the number of inversions in the right subarray.
        long long int right_inversions
            = sort_and_count(array, middle + 1, last);

        // Count the number of split inversions.
        long long int split_inversions
            = merge_and_count_split_inversions(array, first, middle, last);

        return left_inversions + right_inversions + split_inversions;
    } /* Else sort the 2 subarrays and count the number of inversions. */
}

long long int merge_and_count_split_inversions(
    int *array, int first, int middle, int last)
{
    // Create 2 new arrays to hold the existing elements.
    int left_len  = middle - first + 1;
    int right_len = last - middle;

    int *left_array  = (int *)malloc(left_len * sizeof(int));
    int *right_array = (int *)malloc(right_len * sizeof(int));

    // Copy the existing elements into these 2 arrays.
    for (int i = 0; i < left_len; i++)
        left_array[i] = array[first + i];

    for (int j = 0; j < right_len; j++)
        right_array[j] = array[middle + 1 + j];

    // Merge the 2 subarrays according to ascending order,
    // and count the number of inversions.
    int i               = 0;
    int j               = 0;
    int k               = first;
    long long int count = 0;

    while (i < left_len && j < right_len) {
        if (left_array[i] <= right_array[j])
            array[k++] = left_array[i++];
        else {
            array[k++] = right_array[j++];
            count += left_len - i;
        }
    }

    // Copy over the remaining elements, if any.
    while (i < left_len)
        array[k++] = left_array[i++];

    while (j < right_len)
        array[k++] = right_array[j++];

    // Free the 2 subarrays.
    free(left_array);
    free(right_array);

    return count;
}
