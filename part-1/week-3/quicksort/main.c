#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"
#include "helpers.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    int *array = (int *)malloc(num * sizeof(int));

    // Scanning.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    int *copy1 = (int *)malloc(num * sizeof(int));
    int *copy2 = (int *)malloc(num * sizeof(int));
    int *copy3 = (int *)malloc(num * sizeof(int));

    // Copy the elements into 3 different arrays.
    for (int i = 0; i < num; i++)
        copy1[i] = copy2[i] = copy3[i] = array[i];

    int comparisons1 = 0, comparisons2 = 0, comparisons3 = 0;

    quicksort(copy1, 0, num - 1, choose_first_element_as_pivot, &comparisons1);
    quicksort(copy2, 0, num - 1, choose_last_element_as_pivot, &comparisons2);
    quicksort(copy3, 0, num - 1, choose_median_as_pivot, &comparisons3);

    // Comparisons.
    printf("Number of comparisons with first element as pivot: %i\n", comparisons1);
    printf("Number of comparisons with last element as pivot:  %i\n", comparisons2);
    printf("Number of comparisons with median as pivot:        %i\n", comparisons3);

    // Cleanup.
    free(array);
    free(copy1);
    free(copy2);
    free(copy3);
    return 0;
}

