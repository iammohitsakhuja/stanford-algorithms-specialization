#include "Graph.hh"
#include "benchmark.hh"
#include "helpers.hh"

using namespace std;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc < 4) {
        fprintf(stderr,
            "Usage: %s file_name num_vertices source [num_output_vertices] "
            "[vertices...]\n",
            argv[0]);
        return 1;
    }

    // Get the arguments.
    char *file_name = argv[1];
    int n           = atoi(argv[2]);
    int source      = atoi(argv[3]);

    // Get the vertices for which the output is to be shown.
    int num_output_vertices
        = argv[4] ? atoi(argv[4]) : (n >= 200 ? 10 : n / 10);
    int *output_vertices = (int *)malloc(num_output_vertices * sizeof(int));

    // Handle the case when the 4th argument is given.
    if (argv[4]) {
        if (argc != num_output_vertices + 5) {
            fprintf(stderr,
                "You must enter %i vertices after [num_output_vertices]\n",
                num_output_vertices);
            return 2;
        }

        // Get the output vertices.
        for (int i = 0; i < num_output_vertices; i++)
            output_vertices[i] = atoi(argv[5 + i]);
    } else {
        // Generate output vertices randomly.
        srand(time(NULL));
        for (int i = 0; i < num_output_vertices; i++)
            output_vertices[i] = rand() % n + 1; /* Adjusted for indexing */
    }

    // Create a graph.
    Graph G(n);

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_loading_graph         = 0.0;
    double time_calculating_distances = 0.0;

    // Load the graph and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    load_graph_from_file(G, n, file_name);
    getrusage(RUSAGE_SELF, &after);
    time_loading_graph = calculate(&before, &after);

    // Calculate distances from the given source.
    getrusage(RUSAGE_SELF, &before);
    int *distances = G.calculate_distances(source);
    getrusage(RUSAGE_SELF, &after);
    time_calculating_distances = calculate(&before, &after);

    // Print distances.
    printf(" src -> dest (dist)\n");
    for (int i = 0; i < num_output_vertices; i++)
        printf("%4i -> %4i (%4i)\n", source, output_vertices[i],
            distances[output_vertices[i] - 1]);
    printf("\n");

    // Print the benchmark results.
    printf(
        "TIME IN loading graph:          %.3fms\n", time_loading_graph * 1000);
    printf("TIME IN calculating distances:  %.3fms\n",
        time_calculating_distances * 1000);
    printf("TIME IN total:                  %.3fms\n",
        (time_loading_graph + time_calculating_distances) * 1000);

    // Housekeeping.
    free(output_vertices);
    delete[] distances;
    return 0;
}
