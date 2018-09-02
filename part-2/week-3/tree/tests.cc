#include "tests.hh"
#include "helpers.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

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

    // Test that random values that don't exist return `false` on being
    // searched.
    int no_of_values = array.size() <= 100
        ? 10
        : (array.size() <= 100000 ? 100 : (array.size() / 1000));
    for (int i = 0; i < no_of_values; i++) {
        // Choose a random value that doesn't exist in the array.
        int index = rand() % (array.size() - 1);
        int value = (array[index] + array[index + 1]) / 2;
        while (value == array[index]) {
            index = rand() % (array.size() - 1);
            value = (array[index] + array[index + 1]) / 2;
        }

        // Test that this value returns `false` on being searched.
        assert(tree.search(value) == false);
    }
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
    assert(tree.pred(array.front() - 1) == NULL);
    assert(tree.pred(array.back() + 1)->data == array.back());

    // Test that random values that don't exist return the appropriate
    // predecessor.
    int no_of_values = array.size() <= 100
        ? 10
        : (array.size() <= 100000 ? 100 : (array.size() / 1000));
    for (int i = 0; i < no_of_values; i++) {
        // Choose a random value that doesn't exist in the array.
        int index = rand() % (array.size() - 1);
        int value = (array[index] + array[index + 1]) / 2;
        while (value == array[index]) {
            index = rand() % (array.size() - 1);
            value = (array[index] + array[index + 1]) / 2;
        }

        // Test that this value returns the appropriate predecessor.
        assert(tree.pred(value)->data == array[index]);
    }
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
    assert(tree.succ(array.back() + 1) == NULL);
    assert(tree.succ(array.front() - 1)->data == array.front());

    // Test that random values that don't exist return the appropriate
    // successor.
    int no_of_values = array.size() <= 100
        ? 10
        : (array.size() <= 100000 ? 100 : (array.size() / 1000));
    for (int i = 0; i < no_of_values; i++) {
        // Choose a random value that doesn't exist in the array.
        int index = rand() % (array.size() - 1);
        int value = (array[index] + array[index + 1]) / 2;
        while (value == array[index]) {
            index = rand() % (array.size() - 1);
            value = (array[index] + array[index + 1]) / 2;
        }

        // Test that this value returns the appropriate successor.
        assert(tree.succ(value)->data == array[index + 1]);
    }
}

void test_rank(vector<int> &array, Tree &tree)
{
    // Test that the rank of each node in the tree is equal to its upper bound
    // in the sorted array.
    for (size_t i = 0; i < array.size(); i++)
        assert(tree.rank(array[i]) == upper_bound(array, array[i]));
    assert(tree.rank(array.front() - 1) == 0);
    assert(tree.rank(array.back() + 1) == array.size());

    // Test that random values that don't exist return the appropriate rank.
    int no_of_values = array.size() <= 100
        ? 10
        : (array.size() <= 100000 ? 100 : (array.size() / 1000));
    for (int i = 0; i < no_of_values; i++) {
        // Choose a random value that doesn't exist in the array.
        int index = rand() % (array.size() - 1);
        int value = (array[index] + array[index + 1]) / 2;
        while (value == array[index]) {
            index = rand() % (array.size() - 1);
            value = (array[index] + array[index + 1]) / 2;
        }

        // Test that this value returns the appropriate rank.
        assert(tree.rank(value) == index + 1);
    }
}

void test_deletion(vector<int> &array, Tree &tree)
{
    // Test that random values that exist, when deleted - return `false` when
    // searched for.
    int no_of_values = array.size() <= 100
        ? 10
        : (array.size() <= 100000 ? 100 : (array.size() / 1000));

    // Maintain a count of values that will be actually deleted.
    int count = 0;

    for (int i = 0; i < no_of_values; i++) {
        // Choose a random value from the array.
        int index = rand() % array.size();
        int value = array[index];

        // Find out whether this value currently exists in the tree or if it
        // has been deleted already.
        bool value_exists = tree.search(value);

        // Get its rank and size before deletion.
        int rank = tree.rank(value);
        int size = tree.size();

        // Now, try deleting the value.
        tree.pop(value);

        // If value existed before deletion, then its rank and size shoud be
        // one less than before.
        if (value_exists) {
            count++;
            assert(tree.rank(value) == rank - 1);
            assert(tree.size() == size - 1);
        } else { /* Else, they will be the same. */
            assert(tree.rank(value) == rank);
            assert(tree.size() == size);
        }
    }

    assert(tree.size() == array.size() - count);
}

void test_clear_empty_size(vector<int> &array, Tree &tree)
{
    if (tree.empty()) {
        assert(tree.size() == 0);
        return;
    }

    // First clear the tree.
    tree.clear();

    // Check that it is empty now.
    assert(tree.size() == 0);
    assert(tree.empty() == true);
}
