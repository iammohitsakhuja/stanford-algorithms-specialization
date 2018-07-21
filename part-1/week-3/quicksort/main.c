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

    // Printing.
    printf("Array:\n");
    for (int i = 0; i < num; i++)
        printf("%i\n", array[i]);

    quicksort(array, 0, num - 1, choose_first_element_as_pivot);

    // Printing.
    printf("After sorting:\n");
    for (int i = 0; i < num; i++)
        printf("%i\n", array[i]);

    // Cleanup.
    free(array);
    return 0;
}
