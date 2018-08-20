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
    const int n = 12;
    Graph G(n);

    // First cluster.
    G.add_edge(1, 2);
    G.add_edge(1, 6);
    G.add_edge(2, 4);
    G.add_edge(4, 6);
    G.add_edge(4, 7);
    G.add_edge(4, 9);
    G.add_edge(6, 7);
    G.add_edge(7, 9);

    // Second cluster.
    G.add_edge(3, 5);
    G.add_edge(3, 8);
    G.add_edge(5, 8);
    G.add_edge(8, 10);

    // Third cluster contains a self loop. Fourth contains no edges.
    G.add_edge(11, 11);

    // Testing.
    assert(G.get_shortest_path(1, 1) == 0);
    assert(G.get_shortest_path(1, 9) == 3);
    assert(G.get_shortest_path(1, 3) == -1);
    assert(G.get_shortest_path(1, 7) == 2);
    assert(G.get_shortest_path(3, 10) == 2);
    assert(G.get_shortest_path(8, 10) == 1);
    assert(G.get_shortest_path(3, 4) == -1);
    assert(G.get_shortest_path(5, 5) == 0);
    assert(G.get_shortest_path(11, 1) == -1);
    assert(G.get_shortest_path(11, 3) == -1);
    assert(G.get_shortest_path(11, 11) == 0);
    assert(G.get_shortest_path(12, 12) == 0);
}
