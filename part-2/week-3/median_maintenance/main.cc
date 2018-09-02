#include <cstdio>
#include <cstdlib>

#include "DualHeap.hh"
#include "Tree.hh"
#include "benchmark.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

void test(long long int heap_median, long long int tree_median);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num\n", argv[0]);
        return 1;
    }

    // Size of the upcoming input.
    int num = atoi(argv[1]);

    // Get the inputs.
    int *array = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; i++)
        scanf("%i", &array[i]);

    // Create a dual heap (a combination of a min heap and a max heap).
    DualHeap dual_heap;

    // Create a tree.
    Tree tree;

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_calculating_median_via_heap = 0.0;
    double time_calculating_median_via_tree = 0.0;

    // The sum of all medians for a heap and a tree.
    long long int heap_median = 0;
    long long int tree_median = 0;

    // Benchmark the time taken to push each element into the dual heap,
    // and at each point - calculate the median.
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < num; i++) {
        dual_heap.push(array[i]);
        heap_median += dual_heap.median();
    }
    getrusage(RUSAGE_SELF, &after);
    time_calculating_median_via_heap = calculate(&before, &after);

    // Benchmark the time taken to push each element into the tree,
    // and at each point - calculate the median.
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < num; i++) {
        tree.push(array[i]);
        tree_median += tree.select((tree.size() + 1) / 2)->data;
    }
    getrusage(RUSAGE_SELF, &after);
    time_calculating_median_via_tree = calculate(&before, &after);

    // Display the median.
    printf("Median through heap = %lli\n", heap_median);
    printf("Median through tree = %lli\n\n", tree_median);

    // Display the benchmark results.
    printf("TIME IN calculating median via heap: %5.3fms\n",
        time_calculating_median_via_heap * 1000);
    printf("TIME IN calculating median via tree: %5.3fms\n\n",
        time_calculating_median_via_tree * 1000);

    // Tests.
    test(heap_median, tree_median);
    printf("All tests passed!\n");

    // Housekeeping.
    free(array);
    return 0;
}

void test(long long int heap_median, long long int tree_median)
{
    assert(heap_median == tree_median);
}
