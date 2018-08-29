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

    for (int i = 0; i < SIZE; i++)
        tree.insert(inputs[i]);

    list<int> traversed_nodes = tree.traverse();

    int i = 0;
    while (!traversed_nodes.empty()) {
        assert(traversed_nodes.front() == expected_outputs[i++]);
        traversed_nodes.pop_front();
    }
}
