#include "helpers.hh"
#include "benchmark.hh"

void add_edges_to_graph(Graph &graph, int u, int v, int num)
{
    // If vertex > 0, vertex maps to vertex.
    // If vertex < 0, vertex maps to num - vertex i.e. num + |vertex|.
    int u_bar = num + u;
    int v_bar = num + v;

    if (u < 0) {
        u_bar = -u;
        u     = num - u;
    }

    if (v < 0) {
        v_bar = -v;
        v     = num - v;
    }

    // For ever (u or v), add one edge from u_bar to v, and another edge from
    // v_bar to u.
    graph.add_edge(u_bar, v);
    graph.add_edge(v_bar, u);
}

Graph *load_graph_from_file(const char *file_name)
{
    // Open file for reading.
    FILE *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Could not open file for reading: %s\n", file_name);
        return nullptr;
    }

    // Get the number of vertices/clauses.
    int num;
    fscanf(file, "%i", &num);

    // Create a graph with (2 * num + 1) vertices.
    // If x > 0, x maps to x.
    // If x < 0, x maps to n - x i.e. n + |x|.
    // Vertex 0 is unusued.

    Graph *graph = new Graph(2 * num + 1);

    // Read the symbols for each clause, and add edges to the graph for them.
    for (int i = 0; i < num; i++) {
        int src;
        int dest;

        fscanf(file, "%i", &src);
        fscanf(file, "%i", &dest);

        add_edges_to_graph(*graph, src, dest, num);
    }

    // Housekeeping.
    fclose(file);

    return graph;
}

bool get_satisfiability(
    vector<int> strongly_connected_components, int num_vertices)
{
    int n = (num_vertices - 1) / 2;
    for (int i = 1; i <= n; i++)
        if (strongly_connected_components[i]
            == strongly_connected_components[n + i])
            return false;
    return true;
}

bool compute_satisfiability(const char *file_name,
    double &time_loading_graph_from_file, double &time_computing_scc,
    double &time_computing_satisfiability)
{
    // Structures for timing data.
    struct rusage before, after;

    // Load the graph from the file, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    Graph *graph = load_graph_from_file(file_name);
    getrusage(RUSAGE_SELF, &after);
    time_loading_graph_from_file = calculate(&before, &after);

    if (graph == nullptr) {
        fprintf(stderr, "Error occurred in loading graph from file: %s\n",
            file_name);
        exit(4);
    }

    // Compute the SCCs, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    vector<int> strongly_connected_components = graph->compute_sccs();
    getrusage(RUSAGE_SELF, &after);
    time_computing_scc = calculate(&before, &after);

    // Get the satisfiability, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    bool satisfiability = get_satisfiability(
        strongly_connected_components, graph->num_vertices);
    getrusage(RUSAGE_SELF, &after);
    time_computing_satisfiability = calculate(&before, &after);

    return satisfiability;
}
