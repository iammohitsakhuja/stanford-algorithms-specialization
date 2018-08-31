#include <cstdio>

#include "Tree.hh"

#pragma GCC diagnostic ignored "-Wunused-variable"

void test(void);

int main(void)
{
    test();
    printf("\nAll tests passed!\n");
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
    assert(traversed_nodes.empty());
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

    // Remove 2.
    tree.remove(2);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_2[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());

    // Remove 4.
    tree.remove(4);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_4[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());

    // Remove 1.
    tree.remove(1);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_1[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());

    // Remove 9.
    tree.remove(9);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_9[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());

    // Remove 6.
    tree.remove(6);
    traversed_nodes = tree.traverse();
    for (int i = 0; !traversed_nodes.empty(); i++) {
        assert(traversed_nodes.front() == result_after_deleting_6[i]);
        traversed_nodes.pop_front();
    }
    assert(traversed_nodes.empty());

    // First remove the remaining 5 elements, then test whether the root
    // deletion when there's only one single node - goes well.
    for (int i = 0; i < 6; i++)
        tree.remove(result_after_deleting_6[i]);
    assert(tree.traverse().empty());
    printf("Deletion tests passed!\n");
}
