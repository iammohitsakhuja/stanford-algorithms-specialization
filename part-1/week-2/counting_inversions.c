#include <stdio.h>
#include <stdlib.h>

int merge_and_count_split_inv(int *array, int first, int middle, int last);
int sort_and_count(int *array, int first, int last);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    int length = atoi(argv[1]);
    int *array = (int *)malloc(length * sizeof(int));

    // Input.
    for (int i = 0; i < length; i++)
        scanf("%i", &array[i]);

    int inversions = sort_and_count(array, 0, length - 1);

    printf("\nNumber of inversions = %i\n", inversions);

    return 0;
}

int sort_and_count(int *array, int first, int last)
{
    if (first == last)
    {
        return 0;
    }
    else
    {
        int middle = (first + last) / 2;

        int x = sort_and_count(array, first, middle);
        int y = sort_and_count(array, middle + 1, last);
        int z = merge_and_count_split_inv(array, first, middle, last);

        return x + y + z;
    }
}

int merge_and_count_split_inv(int *array, int first, int middle, int last)
{
    // Copy the existing elements into new arrays.
    int left_len = middle - first + 1;
    int right_len = last - middle;

    int *left_array = (int *)malloc(left_len * sizeof(int));
    int *right_array = (int *)malloc(right_len * sizeof(int));

    for (int i = 0; i < left_len; i++)
        left_array[i] = array[first + i];

    for (int j = 0; j < right_len; j++)
        right_array[j] = array[middle + 1 + j];

    // Merge the two subarrays.
    int i = 0;
    int j = 0;
    int k = first;
    int count = 0;

    while (i < left_len && j < right_len)
    {
        if (left_array[i] <= right_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = right_array[j];
            j++;
            count += left_len - i;
        }
        k++;
    }

    // Copy over any remaining elements.
    while (i < left_len)
    {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_len)
    {
        array[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);

    return count;
}