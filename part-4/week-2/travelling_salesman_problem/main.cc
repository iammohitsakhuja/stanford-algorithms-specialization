#include <cmath>
#include <cstdio>
#include <vector>

#include "Point.hh"
#include "benchmark.hh"
#include "helpers.hh"

using namespace std;

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    // Get the inputs.
    char *file_name = argv[1];

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_loading_points_from_file  = 0.0;
    double time_creating_distance_matrix  = 0.0;
    double time_finding_minimum_cost_tour = 0.0;

    // Read the points from the file, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    vector<Point> points = load_points_from_file(file_name);
    getrusage(RUSAGE_SELF, &after);
    time_loading_points_from_file = calculate(&before, &after);

    // Create a distance matrix for these points, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    vector<vector<float>> dist_matrix = create_dist_matrix(points);
    getrusage(RUSAGE_SELF, &after);
    time_creating_distance_matrix = calculate(&before, &after);

    // Find minimum cost tour, and benchmark the time taken.
    getrusage(RUSAGE_SELF, &before);
    float cost = find_minimum_cost_tour(dist_matrix, points);
    getrusage(RUSAGE_SELF, &after);
    time_finding_minimum_cost_tour = calculate(&before, &after);

    // Display the cost of the minimum cost tour.
    printf("Cost of minimum cost tour: %i\n\n", (int)floorf(cost));

    // Display teh benchmark results.
    printf("TIME IN loading points from file:  %6.2fms\n",
        time_loading_points_from_file * 1000);
    printf("TIME IN creating distance matrix:  %6.2fms\n",
        time_creating_distance_matrix * 1000);
    printf("TIME IN finding minimum cost tour:  %6.2fs\n",
        time_finding_minimum_cost_tour);
    printf("TIME IN total:                      %6.2fs\n",
        time_loading_points_from_file + time_creating_distance_matrix
            + time_finding_minimum_cost_tour);

    return 0;
}