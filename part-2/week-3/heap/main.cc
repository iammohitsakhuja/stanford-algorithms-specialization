#include <cstdio>

#include "Heap.hh"
#include "benchmark.hh"

using namespace std;

void test(vector<int> &sorted_elements);
void test_is_heap(Heap &heap);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num\n", argv[0]);
        return 1;
    }

    // Get the input array size.
    const int SIZE = atoi(argv[1]);

    // Create an array to store all the inputs.
    vector<int> array(SIZE);

    // Get the inputs.
    for (int i = 0; i < SIZE; i++)
        scanf("%i", &array[i]);

    // Create 2 heaps.
    Heap single_insert_heap;
    Heap batch_insert_heap;

    // Create vectors to store processed heap elements.
    vector<int> single_insert_elements;
    vector<int> batch_insert_elements;

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_loading_via_single_insertions = 0.0;
    double time_popping_single_insertions     = 0.0;
    double time_loading_via_batch_insertions  = 0.0;
    double time_popping_batch_insertions      = 0.0;

    // Seed for random number generator.
    // (Required for generating random indices).
    srand(time(NULL));

    // Benchmark the time taken to push the elements of the array into the heap
    // one-by-one.
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < SIZE; i++)
        single_insert_heap.push(array[i]);
    getrusage(RUSAGE_SELF, &after);
    time_loading_via_single_insertions = calculate(&before, &after);

    // Benchmark the time taken to heapify the whole array via batch
    // insertions.
    getrusage(RUSAGE_SELF, &before);
    batch_insert_heap.heapify(array);
    getrusage(RUSAGE_SELF, &after);
    time_loading_via_batch_insertions = calculate(&before, &after);

    // Test whether the two heaps formed have the heap property.
    test_is_heap(single_insert_heap);
    test_is_heap(batch_insert_heap);

    // Delete some random keys from the first heap and test whether it still
    // remains a heap.
    for (int i = 0; i < 5; i++) {
        int index = rand() % single_insert_heap.size();
        single_insert_heap.delete_key(index);
        test_is_heap(single_insert_heap);
    }

    // Delete some random keys from the second heap and test whether it still
    // remains a heap.
    for (int i = 0; i < 5; i++) {
        int index = rand() % batch_insert_heap.size();
        batch_insert_heap.delete_key(index);
        test_is_heap(batch_insert_heap);
    }

    // Benchmark the time taken to remove the elements of the first heap from
    // the top one-by-one.
    getrusage(RUSAGE_SELF, &before);
    while (!single_insert_heap.empty()) {
        single_insert_elements.push_back(single_insert_heap.top());
        single_insert_heap.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_single_insertions = calculate(&before, &after);

    // Benchmark the time taken to remove the elements of the second heap from
    // the top one-by-one.
    getrusage(RUSAGE_SELF, &before);
    while (!batch_insert_heap.empty()) {
        batch_insert_elements.push_back(single_insert_heap.top());
        batch_insert_heap.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_batch_insertions = calculate(&before, &after);

    // Display the benchmark results.
    printf("TIME IN loading the heap via single insertions: %6.2fs\n",
        time_loading_via_single_insertions);
    printf("TIME IN loading the heap via batch insertions:  %6.2fs\n",
        time_loading_via_batch_insertions);
    printf("TIME IN popping after single insertions:        %6.2fs\n",
        time_popping_single_insertions);
    printf("TIME IN popping after batch insertions:         %6.2fs\n",
        time_popping_batch_insertions);
    printf("TOTAL TIME IN single insertions method:         %6.2fs\n",
        time_loading_via_single_insertions + time_popping_single_insertions);
    printf("TOTAL TIME IN batch insertions method:          %6.2fs\n",
        time_loading_via_batch_insertions + time_popping_batch_insertions);
    printf("TIME IN total:                                  %6.2fs\n",
        time_loading_via_single_insertions + time_popping_single_insertions
            + time_loading_via_batch_insertions
            + time_popping_batch_insertions);

    test(single_insert_elements);
    test(batch_insert_elements);
    printf("\nAll tests passed!\n");

    // Housekeeping.
    return 0;
}

void test(vector<int> &sorted_elements)
{
    for (unsigned int i = 1; i < sorted_elements.size(); i++)
        assert(sorted_elements[i] >= sorted_elements[i - 1]);
}

void test_is_heap(Heap &heap)
{
    assert(heap.is_heap());
}
