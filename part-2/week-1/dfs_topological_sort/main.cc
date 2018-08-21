#include <iostream>

#include "Graph.hh"

using namespace std;

void test(void);

int main(void)
{
    test();
    printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    // Setup.
    const int n = 6;
    Graph G(n);
    G.add_directed_edge(3, 4);
    G.add_directed_edge(4, 2);
    G.add_directed_edge(5, 1);
    G.add_directed_edge(5, 2);
    G.add_directed_edge(6, 1);
    G.add_directed_edge(6, 3);

    // Test.
    list<int> sorted_vertices    = G.topological_sort();
    const int expected_output[n] = { 6, 5, 3, 4, 2, 1 };
    for (int i = 0; i < n; i++) {
        assert(sorted_vertices.front() == expected_output[i]);
        sorted_vertices.pop_front();
    }
    assert(sorted_vertices.empty());
    printf("Vertices have been sorted topologically!\n");
}
