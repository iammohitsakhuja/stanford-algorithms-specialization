#include <iostream>
#include <list>
#include <set>

#include "Graph.hh"
#include "benchmark.hh"
#include "tests.hh"

using namespace std;

void test(void);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 3) {
        fprintf(stderr, "Usage: %s vertices edges\n", argv[0]);
        return 1;
    }

    int num   = atoi(argv[1]);
    int edges = atoi(argv[2]);

    // Generate a graph.
    Graph G(num);
    while (edges--) {
        int v, w;
        scanf("%i %i ", &v, &w);
        G.add_edge(v, w, true);
    }

    // Before computing the SCC, test whether other graph operations are
    // working perfectly.
    test_bfs();
    test_get_shortest_path();
    test_find_connected_components();
    test_dfs();
    test_topological_sort();
    test_reverse(G);
    printf("All tests passed!\n\n");

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks
    double time_computing_sccs = 0.0;

    // Benchmark the time taken to compute SCCs.
    getrusage(RUSAGE_SELF, &before);
    list<list<int>> strongly_connected_components = G.compute_scc();
    getrusage(RUSAGE_SELF, &after);
    time_computing_sccs = calculate(&before, &after);
    printf("SCCs computed successfully!\n");

    // Calculate the number of elements in each SCC.
    set<int, greater<int>> largest_scc;
    while (!strongly_connected_components.empty()) {
        // Get the size of the current SCC and insert it into the set.
        largest_scc.insert(strongly_connected_components.front().size());

        // Clear the current SCC list.
        strongly_connected_components.front().clear();

        // Remove the list from the list of lists.
        strongly_connected_components.pop_front();
    }

    // Print top 5 largest SCC.
    printf("The sizes of the largest (at most 5) SCCs are: ");
    for (int count = 0; count < 5 && !largest_scc.empty(); count++) {
        printf("%i ", *largest_scc.begin());
        largest_scc.erase(largest_scc.begin());
    }
    printf("\n");

    // Display the benchmark results.
    printf("TIME in computing SCCs: %5.2fs\n", time_computing_sccs);

    // Housekeeping.
    largest_scc.clear();

    return 0;
}
