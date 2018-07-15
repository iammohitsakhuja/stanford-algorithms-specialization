#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int first, int middle, int last);
void merge_sort(int *array, int first, int last);

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

    // Printing.
    // printf("Before sorting...\n");
    // for (int i = 0; i < length; i++)
    //     printf("%i ", array[i]);
    // printf("\n\n");

    // Sort.
    merge_sort(array, 0, length - 1);

    // Print the sorted array.
    // printf("After sorting...\n");
    // for (int i = 0; i < length; i++)
    //     printf("%i ", array[i]);
    // printf("\n");

    // Housekeeping.
    free(array);
    return 0;
}

void merge_sort(int *array, int first, int last)
{
    if (first == last)
    {
        return;
    }
    else
    {
        int middle = (first + last) / 2;

        // Sort the left array.
        merge_sort(array, first, middle);

        // Sort the right array.
        merge_sort(array, middle + 1, last);

        // Merge the two arrays.
        merge(array, first, middle, last);

        return;
    }
}

void merge(int *array, int first, int middle, int last)
{
    // Copy the existing elements into new arrays.
    int left_len = middle - first + 1;
    int right_len = last - middle;

    int *left_array = (int *)malloc(left_len * sizeof(int));
    int *right_array = (int *)malloc((last - middle) * sizeof(int));

    for (int i = 0; i < left_len; i++)
        left_array[i] = array[first + i];

    for (int j = 0, length = last - middle; j < length; j++)
        right_array[j] = array[middle + 1 + j];

    // Merge the two subarrays.
    int i = 0;
    int j = 0;
    int k = first;

    while (i < left_len && j < right_len)
    {
        if (left_array[i] < right_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = right_array[j];
            j++;
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
}