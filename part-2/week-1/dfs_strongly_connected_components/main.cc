#include <iostream>
#include <list>
#include <set>

#include "Graph.hh"

using namespace std;

void test(void);

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s vertices edges\n", argv[0]);
        return 1;
    }

    int num   = atoi(argv[1]);
    int edges = atoi(argv[2]);

    Graph G(num);
    while (edges--) {
        int v, w;
        scanf("%i %i ", &v, &w);
        G.add_directed_edge(v, w);
    }

    list<list<int>> strongly_connected_components = G.compute_scc();
    set<int, greater<int>> largest_scc;
    while (!strongly_connected_components.empty()) {
        int count = 0;

        while (!strongly_connected_components.front().empty()) {
            count++;
            strongly_connected_components.front().pop_front();
        }

        strongly_connected_components.pop_front();
        largest_scc.insert(count);
    }

    // Print largest SCC.
    for (set<int>::iterator it = largest_scc.begin(); it != largest_scc.end();
         it++)
        printf("%i ", *it);
    printf("\n");

    // test();
    // printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    // Setup.
    const int n = 9;
    Graph G(n);
    G.add_directed_edge(1, 4);
    G.add_directed_edge(2, 8);
    G.add_directed_edge(3, 6);
    G.add_directed_edge(4, 7);
    G.add_directed_edge(5, 2);
    G.add_directed_edge(6, 9);
    G.add_directed_edge(7, 1);
    G.add_directed_edge(8, 5);
    G.add_directed_edge(8, 6);
    G.add_directed_edge(9, 3);
    G.add_directed_edge(9, 7);

    list<list<int>> strongly_connected_components = G.compute_scc();
}