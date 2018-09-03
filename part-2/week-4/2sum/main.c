#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "benchmark.h"
#include "hash_table.h"
#include "helpers.h"

int collisions = 0;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 5) {
        fprintf(
            stderr, "Usage: %s <file_name> <num> <start> <end>\n", argv[0]);
        return 1;
    }

    // Get the required inputs.
    const char *FILE_NAME = argv[1];
    const int SIZE        = atoi(argv[2]);
    int64_t start         = atoll(argv[3]);
    int64_t end           = atoll(argv[4]);

    // Create an array and load the numbers into it (needed for faster
    // iteration at the cost of more memory).
    int64_t *array = load_from_file(FILE_NAME, SIZE);

    // Safety check.
    if (!array)
        return 2;

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_load     = 0.0;
    double time_unload   = 0.0;
    double time_counting = 0.0;

    // Load the numbers into a hash table and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    Node **hash_table = load(array, SIZE);
    getrusage(RUSAGE_SELF, &after);
    time_load = calculate(&before, &after);

    // Safety check.
    if (!hash_table) {
        free(array);
        return 3;
    }

    // Calculate the number of target values that can be achieved from the
    // given data set of numbers, and benchmark the time taken to do it.
    getrusage(RUSAGE_SELF, &before);
    int count = count_achievable_targets(
        array, SIZE, (const Node **)hash_table, start, end);
    getrusage(RUSAGE_SELF, &after);
    time_counting = calculate(&before, &after);

    // Unload the hash table and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    unload(hash_table);
    getrusage(RUSAGE_SELF, &after);
    time_unload = calculate(&before, &after);

    printf("Number of collisions:        %6i\n", collisions);
    printf("Count of achievable targets: %6i\n\n", count);

    // Display the benchmark results.
    printf("TIME IN loading:   %7.2fs\n", time_load);
    printf("TIME IN unloading: %7.2fs\n", time_unload);
    printf("TIME IN counting:  %7.2fs\n", time_counting);
    printf("TIME IN total:     %7.2fs\n",
        time_load + time_counting + time_unload);

    // Housekeeping.
    free(array);
    return 0;
}
