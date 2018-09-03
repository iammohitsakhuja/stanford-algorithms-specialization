#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

int64_t *load_from_file(const char *FILE_NAME, size_t SIZE)
{
    // Open the file for reading.
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        fprintf(stderr, "Error in opening the given file\n");
        return NULL;
    }

    // Allocate memory for the array.
    int64_t *array = (int64_t *)malloc(SIZE * sizeof(int64_t));

    // Safety check.
    if (!array) {
        fprintf(stderr, "Error in allocating memory to the array\n");
        fclose(file);
        return NULL;
    }

    // Read from the file and store the values in the array.
    int64_t data = 0;
    for (size_t i = 0; i < SIZE && fscanf(file, "%lli", &data) != EOF; i++)
        array[i] = data;

    // Housekeeping.
    fclose(file);

    return array;
}

int count_achievable_targets(const int64_t *array, size_t SIZE,
    const Node **hash_table, int64_t start, int64_t end)
{
    // Initially, no target values have been achieved.
    int count = 0;

    // Iterate over all target values.
    for (int64_t target = start; target <= end; target++) {
        // printf("Current target: %i ", target);
        // Iterate over all the elements in the array, and check if the other
        // part of the sum exists in the numbers provided.
        for (size_t i = 0; i < SIZE; i++) {
            int64_t x = target - array[i];

            // Only lookup when numbers are distinct.
            if (x != array[i])
                if (check(hash_table, x)) {
                    // printf("Current array[i]: %i ", array[i]);
                    // printf("Current x: %i", x);
                    count += 1;
                    break;
                }
        }
        // printf("\n");
    }

    return count;
}
