#include <iostream>
#include "helpers.hpp"
#include "rselect.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s num order\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int num = atoi(argv[1]);
    int order = atoi(argv[2]);

    int *array = (int *)malloc(num * sizeof(int));

    // Scanning.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    int element = rselect(array, 0, num - 1, order, choose_random_pivot);
    printf("Element at %i order = %i\n", order, element);

    // Printing.
    // for (int i = 0; i < num; i++)
    //     printf("%i\n", array[i]);

    free(array);
    return 0;
}

