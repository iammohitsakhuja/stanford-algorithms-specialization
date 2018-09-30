#include <cstdio>
#include <cstdlib>

#include "benchmark.hh"
#include "helpers.hh"

using namespace std;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num_graphs> [...filenames]\n", argv[0]);
        return 1;
    }

    // Further ensure proper usage.
    int num_graphs = atoi(argv[1]);
    if (num_graphs <= 0) {
        fprintf(stderr, "Number of graphs must be greater than 0\n");
        return 2;
    }

    if (argc != num_graphs + 2) {
        fprintf(stderr,
            "Number of filenames provided must be the same as as the number "
            "entered in the num_graphs argument\n");
        return 3;
    }

    // Store the inputs.
    char *file_names[num_graphs];
    for (int i = 0; i < num_graphs; i++)
        file_names[i] = argv[2 + i];

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    vector<double> time_loading_graphs(num_graphs, 0.0);
    vector<double> time_calculating_shortest_paths(num_graphs, 0.0);
    double         total_time_loading_graphs             = 0.0;
    double         total_time_calculating_shortest_paths = 0.0;

    // Load graphs from files and benchmark the time taken.
    Graph *graphs[num_graphs];
    for (int i = 0; i < num_graphs; i++) {
        getrusage(RUSAGE_SELF, &before);
        graphs[i] = load_graph_from_file(file_names[i]);
        getrusage(RUSAGE_SELF, &after);
        time_loading_graphs[i] = calculate(&before, &after);
        total_time_loading_graphs += time_loading_graphs[i];

        if (graphs[i] == NULL) {
            fprintf(stderr, "File not found: %s\n", file_names[i]);
            return 4;
        }
    }

    // Calculate the shortest path distance for each graph, and display and
    // benchmark the result.
    int min_distance = INT_MAX;
    for (int graph = 0; graph < num_graphs; graph++) {
        vector<vector<int>> all_pairs_shortest_path_distances;

        getrusage(RUSAGE_SELF, &before);
        try {
            all_pairs_shortest_path_distances
                = graphs[graph]->johnsons_algorithm();
        } catch (CycleExistsException &ex) {
            getrusage(RUSAGE_SELF, &after);
            time_calculating_shortest_paths[graph]
                = calculate(&before, &after);
            total_time_calculating_shortest_paths
                += time_calculating_shortest_paths[graph];

            printf("Graph %2i: %s\n", graph + 1, ex.what());
            continue;
        }

        // Find the shortest shortest distance.
        for (int i = 0; i < all_pairs_shortest_path_distances.size(); i++)
            for (int j = 0; j < all_pairs_shortest_path_distances[i].size();
                 j++)
                if (all_pairs_shortest_path_distances[i][j] < min_distance)
                    min_distance = all_pairs_shortest_path_distances[i][j];
        getrusage(RUSAGE_SELF, &after);
        time_calculating_shortest_paths[graph] = calculate(&before, &after);
        total_time_calculating_shortest_paths
            += time_calculating_shortest_paths[graph];

        printf("Shortest path distance for graph %i: %i\n", graph + 1,
            min_distance);
    }
    printf("\n");

    // Display the final result.
    if (min_distance != INT_MAX)
        printf("Shortest shortest path distance: %i\n\n", min_distance);
    else
        printf("No shortest shortest path distance for the given graphs!\n\n");

    // Display the benchmark results.
    for (int i = 0; i < num_graphs; i++)
        printf("TIME IN loading graph %i:                        %8.2fs\n",
            i + 1, time_loading_graphs[i]);
    printf("\n");

    for (int i = 0; i < num_graphs; i++)
        printf("TIME IN calculating shortest paths for graph %i: %8.2fs\n",
            i + 1, time_calculating_shortest_paths[i]);
    printf("\n");

    printf("TOTAL TIME IN loading graphs:                   %8.2fs\n",
        total_time_loading_graphs);
    printf("TOTAL TIME in calculating shortest paths:       %8.2fs\n\n",
        total_time_calculating_shortest_paths);

    printf("TIME IN TOTAL:                                  %8.2fs\n",
        total_time_loading_graphs + total_time_calculating_shortest_paths);

    return 0;
}