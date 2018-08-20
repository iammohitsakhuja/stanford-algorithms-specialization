#include <iostream>

#include "Graph.hh"

#pragma GCC diagnostic ignored "-Wunused-variable"

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
    const int n = 10;
    Graph G(n);

    // First cluster.
    G.add_edge(1, 3);
    G.add_edge(1, 5);
    G.add_edge(3, 5);
    G.add_edge(5, 7);
    G.add_edge(5, 9);

    // Second cluster.
    G.add_edge(2, 4);

    // Third cluster.
    G.add_edge(6, 8);
    G.add_edge(6, 10);
    G.add_edge(8, 10);

    // Testing.
    vector<list<int>> connected_components = G.find_connected_components();
    assert(connected_components.size() == 3);

    // Testing the values of each of those components.
    const int expected_components[3][5]
        = { { 1, 5, 3, 9, 7 }, { 2, 4 }, { 6, 10, 8 } };
    for (int i = 0, size = connected_components.size(); i < size; i++) {
        int j = 0;
        while (!connected_components[i].empty()) {
            assert(connected_components[i].front()
                == expected_components[i][j++]);
            connected_components[i].pop_front();
        }
        assert(connected_components[i].empty());
        printf("Component %i tests passed!\n", i + 1);
    }
    printf("\n");
}
