#include <algorithm>
#include <cstdio>
#include <vector>

#include "Tree.hh"
#include "benchmark.hh"
#include "tests.hh"

using namespace std;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num\n", argv[0]);
        return 1;
    }

    // Get the size of the input.
    int num = atoi(argv[1]);

    // Create an array to store all the inputs.
    vector<int> array(num);

    // Get the inputs.
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_sorting_array = 0.0;
    double time_insertion     = 0.0;
    double time_traversal     = 0.0;
    double time_searching     = 0.0;
    double time_selection     = 0.0;
    double time_min_max       = 0.0;
    double time_predecessor   = 0.0;
    double time_successor     = 0.0;
    double time_ranking       = 0.0;
    double time_deletion      = 0.0;
    double time_clearing      = 0.0;

    // Create a tree.
    Tree tree;

    // Benchmark and test insertion.
    getrusage(RUSAGE_SELF, &before);
    test_insertion(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_insertion = calculate(&before, &after);
    printf("Insertion tests passed!\n");

    // Benchmark the time taken to sort the array after insertion into the tree
    // is done.
    getrusage(RUSAGE_SELF, &before);
    sort(array.begin(), array.end());
    getrusage(RUSAGE_SELF, &after);
    time_sorting_array = calculate(&before, &after);
    printf("Actual array sorted!\n");

    // Benchmark and test traversal.
    getrusage(RUSAGE_SELF, &before);
    test_traversal(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_traversal = calculate(&before, &after);
    printf("In-order traversal tests passed!\n");

    // Benchmark and test searching.
    getrusage(RUSAGE_SELF, &before);
    test_searching(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_searching = calculate(&before, &after);
    printf("Searching tests passed!\n");

    // Benchmark and test selection.
    getrusage(RUSAGE_SELF, &before);
    test_selection(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_selection = calculate(&before, &after);
    printf("Selection tests passed!\n");

    // Benchmark and test min/max.
    getrusage(RUSAGE_SELF, &before);
    test_min_max(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_min_max = calculate(&before, &after);
    printf("Min/max tests passed!\n");

    // Benchmark and test predecessor.
    getrusage(RUSAGE_SELF, &before);
    test_predecessor(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_predecessor = calculate(&before, &after);
    printf("Predecessor tests passed!\n");

    // Benchmark and test successor.
    getrusage(RUSAGE_SELF, &before);
    test_successor(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_successor = calculate(&before, &after);
    printf("Successor tests passed!\n");

    // Benchmark and test rank.
    getrusage(RUSAGE_SELF, &before);
    test_rank(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_ranking = calculate(&before, &after);
    printf("Rank tests passed!\n");

    // Benchmark and test deletion.
    getrusage(RUSAGE_SELF, &before);
    test_deletion(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_deletion = calculate(&before, &after);
    printf("Deletion tests passed!\n");

    // Benchmark and test clearing.
    getrusage(RUSAGE_SELF, &before);
    test_clear_empty_size(array, tree);
    getrusage(RUSAGE_SELF, &after);
    time_clearing = calculate(&before, &after);
    printf("Clearing tests passed!\n");

    printf("\nAll tests passed!\n\n");

    // Display the benchmark results.
    printf("TIME IN insertion and its testing:            %5.2fs\n",
        time_insertion);
    printf("TIME IN sorting the array:                    %5.2fs\n",
        time_sorting_array);
    printf("TIME IN traversal and its testing:            %5.2fs\n",
        time_traversal);
    printf("TIME IN searching and its testing:            %5.2fs\n",
        time_searching);
    printf("TIME IN selection and its testing:            %5.2fs\n",
        time_selection);
    printf("TIME IN min/max and its testing:              %5.2fs\n",
        time_min_max);
    printf("TIME IN finding predecessors and its testing: %5.2fs\n",
        time_predecessor);
    printf("TIME IN finding successors and its testing:   %5.2fs\n",
        time_successor);
    printf("TIME IN ranking and its testing:              %5.2fs\n",
        time_ranking);
    printf("TIME IN deletion and its testing:             %5.2fs\n",
        time_deletion);
    printf("TIME IN clearing the tree and its testing:    %5.2fs\n",
        time_clearing);

    printf("TIME IN total (excluding sorting the array):  %5.2fs\n",
        time_insertion + time_traversal + time_searching + time_selection
            + time_min_max + time_predecessor + time_successor + time_deletion
            + time_clearing);

    return 0;
}
