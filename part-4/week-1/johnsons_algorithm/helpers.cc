#include "helpers.hh"

Graph *load_graph_from_file(const char *file_name)
{
    // Open the file for reading.
    FILE *file = fopen(file_name, "r");
    if (!file)
        return NULL;

    // Read the number of vertices and edges in the Graph.
    int num_vertices = 0;
    int num_edges    = 0;
    fscanf(file, "%i", &num_vertices);
    fscanf(file, "%i", &num_edges);

    // Create a graph with the given number of vertices.
    Graph *graph = new Graph(num_vertices);

    // Read each edge's src, dest and weight, and add it to the graph.
    for (int i = 0; i < num_edges && !feof(file); i++) {
        int src    = 0;
        int dest   = 0;
        int weight = 0;

        fscanf(file, "%i", &src);
        fscanf(file, "%i", &dest);
        fscanf(file, "%i", &weight);

        graph->add_edge(src, dest, weight);
    }

    // Housekeeping.
    fclose(file);

    return graph;
}
