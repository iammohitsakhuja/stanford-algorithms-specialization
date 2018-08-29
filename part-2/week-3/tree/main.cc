#include <cstdio>

#include "Tree.hh"

void test(void);

int main(void)
{
    test();
    printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    const int SIZE             = 11;
    int inputs[SIZE]           = { 6, 3, 2, 1, 4, 5, 9, 7, 8, 11, 10 };
    int expected_outputs[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    Tree tree;

    // Insert elements into the tree.
    for (int i = 0; i < SIZE; i++)
        tree.insert(inputs[i]);

    // Tests for traversing the tree.
    list<int> traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == expected_outputs[i]);
        traversed_nodes.pop_front();
    }
    printf("Tree traversed (in order) successfully!\n");

    // Tests for searching.
    for (int i = 0; i < SIZE; i++)
        assert(tree.search(inputs[i]));
    assert(tree.search(-1) == false);
    assert(tree.search(12) == false);
    printf("Searching tests passed successfully!\n");

    // Tests for selecting ith order element.
    for (int i = 0; i < SIZE; i++)
        assert(tree.select(i + 1)->data == i + 1);
    assert(tree.select(0) == NULL);
    assert(tree.select(SIZE + 1) == NULL);
    printf("Selecting tests passed successfully!\n");

    // Tests for min/max.
    assert(tree.min()->data == 1);
    assert(tree.max()->data == 11);
    printf("Min/max tests passed successfully!\n");

    // Tests for predecessor and successor.
    assert(tree.pred(1) == NULL);
    for (int i = 2; i <= SIZE; i++)
        assert(tree.pred(i)->data == i - 1);
    for (int i = 1; i < SIZE; i++)
        assert(tree.succ(i)->data == i + 1);
    assert(tree.succ(11) == NULL);
    printf("Predecessor and successor tests passed successfully!\n");

    // Tests for rank.
    for (int i = 1; i <= SIZE; i++)
        assert(tree.rank(i) == i);
    printf("Rank tests passed!\n");
}
