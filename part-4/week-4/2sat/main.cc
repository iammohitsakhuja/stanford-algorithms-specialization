#include <cstdio>
#include <cstdlib>

#include "Graph.hh"
#include "helpers.hh"

using namespace std;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc < 2) {
        fprintf(stderr, "Usage: %s num_files file_names...\n", argv[0]);
        return 1;
    }

    // Further ensure proper usage.
    int num_files = atoi(argv[1]);
    if (num_files == 0) {
        fprintf(stderr, "Number of files must be a positive integer\n");
        return 2;
    }
    if (argc != num_files + 2) {
        fprintf(
            stderr, "Must provide same number of file names as num_files\n");
        return 3;
    }

    // Get the inputs.
    char *file_names[num_files];
    for (int i = 0; i < num_files; i++)
        file_names[i] = argv[2 + i];

    // Benchmarks.
    double time_loading_graph_from_file[num_files];
    double time_computing_scc[num_files];
    double time_computing_satisfiability[num_files];
    double total_time_loading_graphs           = 0.0;
    double total_time_computing_sccs           = 0.0;
    double total_time_computing_satisfiability = 0.0;

    // Array to store the satisfiability for each file in the input.
    bool satisfiability[num_files];

    // Get the satisfiability for each file in the input, and display the
    // results.
    for (int i = 0; i < num_files; i++) {
        satisfiability[i] = compute_satisfiability(file_names[i],
            time_loading_graph_from_file[i], time_computing_scc[i],
            time_computing_satisfiability[i]);
        printf("File %i: %s\n", i + 1,
            satisfiability[i] ? "Satisfiable" : "Non-satisfiable");
    }
    printf("\n");

    // Display the benchmark results.
    printf("BENCHMARK RESULTS:\n");
    for (int i = 0; i < num_files; i++) {
        printf("TIME IN loading graph %i:                      %6.3fs\n",
            i + 1, time_loading_graph_from_file[i]);
        total_time_loading_graphs += time_loading_graph_from_file[i];
    }
    printf("\n");

    for (int i = 0; i < num_files; i++) {
        printf("TIME IN computing SCCs for graph %i:           %6.3fs\n",
            i + 1, time_computing_scc[i]);
        total_time_computing_sccs += time_computing_scc[i];
    }
    printf("\n");

    for (int i = 0; i < num_files; i++) {
        printf("TIME IN computing satisfiability for graph %i: %6.3fs\n",
            i + 1, time_computing_satisfiability[i]);
        total_time_computing_satisfiability
            += time_computing_satisfiability[i];
    }
    printf("\n");

    printf("TOTAL TIME IN loading graphs:                 %6.3fs\n",
        total_time_loading_graphs);
    printf("TOTAL TIME IN computing sccs:                 %6.3fs\n",
        total_time_computing_sccs);
    printf("TOTAL TIME IN computing satisfiability:       %6.3fs\n\n",
        total_time_computing_satisfiability);

    printf("TOTAL TIME:                                   %6.3fs\n",
        total_time_loading_graphs + total_time_computing_sccs
            + total_time_computing_satisfiability);

    return 0;
}
