#include <algorithm>
#include <cstdio>
#include <vector>

#include "Tree.hh"
#include "benchmark.hh"
#include "helpers.hh"

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

void test(void);

void test_insertion(vector<int> &array, Tree &tree);
void test_traversal(vector<int> &array, Tree &tree);
void test_searching(vector<int> &array, Tree &tree);
void test_selection(vector<int> &array, Tree &tree);
void test_min_max(vector<int> &array, Tree &tree);
void test_predecessor(vector<int> &array, Tree &tree);
void test_successor(vector<int> &array, Tree &tree);
void test_rank(vector<int> &array, Tree &tree);

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
    double time_rank          = 0.0;

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
    time_rank = calculate(&before, &after);
    printf("Rank tests passed!\n");

    printf("\nAll tests passed!\n");

    return 0;
}

void test_insertion(vector<int> &array, Tree &tree)
{
    // Insert elements into the array.
    for (size_t i = 0; i < array.size(); i++)
        tree.push(array[i]);
    assert(tree.size() == array.size());
}

void test_traversal(vector<int> &array, Tree &tree)
{
    // Traverse the tree.
    list<int> traversed_nodes = tree.traverse();
    for (size_t i = 0; !traversed_nodes.empty() || i < array.size(); i++) {
        assert(traversed_nodes.front() == array[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
}

void test_searching(vector<int> &array, Tree &tree)
{
    // Test that every element from the array is searchable.
    for (size_t i = 0; i < array.size(); i++)
        assert(tree.search(array[i]));
    assert(tree.search(array[0] - 1) == false);
    assert(tree.search(array[array.size() - 1] + 1) == false);
}

void test_selection(vector<int> &array, Tree &tree)
{
    // Test whether the ith order element of tree is equal to the ith order
    // element in the array.
    for (size_t i = 0; i < array.size(); i++)
        assert(tree.select(i + 1)->data == array[i]);

    assert(tree.select(0) == NULL);
    assert(tree.select(array.size() + 1) == NULL);
}

void test_min_max(vector<int> &array, Tree &tree)
{
    // Minimum element is the first element of the sorted array.
    assert(tree.min()->data == array.front());

    // Maximum element is the last element of the sorted array.
    assert(tree.max()->data == array.back());
}

void test_predecessor(vector<int> &array, Tree &tree)
{
    // Test that the predecessor of each element (if it exists) is the element
    // at the index `lowerbound - 1` in the array.
    for (size_t i = 0; i < array.size(); i++) {
        int pred_index = lower_bound(array, array[i]) - 1;

        if (pred_index == -1 && array[pred_index + 1] == array[i])
            assert(tree.pred(array[i]) == NULL);
        else
            assert(tree.pred(array[i])->data == array[pred_index]);
    }
    assert(tree.pred(array.back() + 1)->data == array.back());
}

void test_successor(vector<int> &array, Tree &tree)
{
    // Test that the successor of each element (if it exists) is the element at
    // the index `upperbound` in the array.
    for (size_t i = 0; i < array.size(); i++) {
        int succ_index = upper_bound(array, array[i]);

        if (succ_index == (int)array.size()
            && array[succ_index - 1] == array[i])
            assert(tree.succ(array[i]) == NULL);
        else
            assert(tree.succ(array[i])->data == array[succ_index]);
    }
    assert(tree.succ(array.front() - 1)->data == array.front());
}

void test_rank(vector<int> &array, Tree &tree)
{
    // Test that the rank of each node in the tree is equal to its upper bound
    // in the sorted array.
    for (size_t i = 0; i < array.size(); i++)
        assert(tree.rank(array[i]) == upper_bound(array, array[i]));
}

void test(void)
{
    int SIZE               = 11;
    int inputs[]           = { 6, 3, 2, 1, 4, 5, 9, 7, 8, 11, 10 };
    int expected_outputs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    Tree tree;

    // Insert elements into the tree.
    for (int i = 0; i < SIZE; i++)
        tree.push(inputs[i]);
    assert(tree.size() == SIZE);
    printf("Tree size is correct!\n");

    // Tests for traversing the tree.
    list<int> traversed_nodes = tree.traverse();
    // for (int i = 0; !traversed_nodes.empty(); i++) {
    //     assert(traversed_nodes.front() == expected_outputs[i]);
    //     traversed_nodes.pop_front();
    // }
    // assert(traversed_nodes.empty());
    // printf("Tree traversed (in order) successfully!\n");
    //
    // // Tests for searching.
    // for (int i = 0; i < SIZE; i++)
    //     assert(tree.search(inputs[i]));
    // assert(tree.search(-1) == false);
    // assert(tree.search(12) == false);
    // printf("Searching tests passed successfully!\n");
    //
    // // Tests for selecting ith order element.
    // for (int i = 0; i < SIZE; i++)
    //     assert(tree.select(i + 1)->data == i + 1);
    // assert(tree.select(0) == NULL);
    // assert(tree.select(SIZE + 1) == NULL);
    // printf("Selecting tests passed successfully!\n");
    //
    // // Tests for min/max.
    // assert(tree.min()->data == 1);
    // assert(tree.max()->data == 11);
    // printf("Min/max tests passed successfully!\n");
    //
    // // Tests for predecessor and successor.
    // assert(tree.pred(1) == NULL);
    // for (int i = 2; i <= SIZE; i++)
    //     assert(tree.pred(i)->data == i - 1);
    // for (int i = 1; i < SIZE; i++)
    //     assert(tree.succ(i)->data == i + 1);
    // assert(tree.succ(11) == NULL);
    // printf("Predecessor and successor tests passed successfully!\n");

    // Tests for rank.
    // for (int i = 1; i <= SIZE; i++)
    //     assert(tree.rank(i) == i);
    // printf("Rank tests passed!\n");

    // Tests for deletion.
    // 1 left child branch.
    int result_after_deleting_2[] = { 1, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    // 1 right child branch.
    int result_after_deleting_4[] = { 1, 3, 5, 6, 7, 8, 9, 10, 11 };
    // No child i.e. leaf node.
    int result_after_deleting_1[] = { 3, 5, 6, 7, 8, 9, 10, 11 };
    // Both child branches.
    int result_after_deleting_9[] = { 3, 5, 6, 7, 8, 10, 11 };
    // Deleting the root.
    int result_after_deleting_6[] = { 3, 5, 7, 8, 10, 11 };

    // Make sure the size is right.
    assert(tree.size() == SIZE);

    // Remove 2.
    tree.pop(2);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_2[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
    assert(tree.size() == --SIZE);

    // Remove 4.
    tree.pop(4);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_4[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
    assert(tree.size() == --SIZE);

    // Remove 1.
    tree.pop(1);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_1[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
    assert(tree.size() == --SIZE);

    // Remove 9.
    tree.pop(9);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_9[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
    assert(tree.size() == --SIZE);

    // Remove 6.
    tree.pop(6);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_6[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());
    assert(tree.size() == --SIZE);

    // First remove the remaining 5 elements, then test whether the root
    // deletion when there's only one single node - goes well.
    for (int i = 0; i < 6; i++)
        tree.pop(result_after_deleting_6[i]);
    assert(tree.traverse().empty());
    assert(tree.size() == 0);
    assert(tree.empty());
    printf("Deletion tests passed!\n");
}
