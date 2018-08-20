#include "Point.hh"
#include "benchmark.hh"
#include "constants.hh"
#include "helper.hh"
#include <cassert>
#include <iostream>

using namespace std;

void test(Pair *brute_force_pair, Pair *closest_points_pair);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    // Create an array to store all points.
    int n         = atoi(argv[1]);
    Point *points = (Point *)malloc(n * sizeof(Point));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_brute_force = 0.0, time_closest_pair_algorithm = 0.0;

    // Scan all points.
    for (int i = 0; i < n; i++)
        points[i].scan();

    // Benchmark the time taken to find the closest pair by brute force.
    getrusage(RUSAGE_SELF, &before);
    Pair *brute_force_pair = brute_force(points, n);
    getrusage(RUSAGE_SELF, &after);
    time_brute_force = calculate(&before, &after);

    // Benchmark the time taken to find the closest pair by the O(nlogn)
    // algorithm.
    getrusage(RUSAGE_SELF, &before);
    Pair *closest_points_pair = find_closest_pair(points, n);
    getrusage(RUSAGE_SELF, &after);
    time_closest_pair_algorithm = calculate(&before, &after);

    printf("Closest pair according to brute force:\n");
    brute_force_pair->print();
    printf("\n");

    printf("Closest pair according to O(nlogn) algorithm:\n");
    closest_points_pair->print();
    printf("\n");

    // Display the benchmark results.
    printf("TIME IN calculating result by brute force:             %.2f\n",
        time_brute_force);
    printf("TIME IN calculating result by closest pair algorithm:  %.2f\n",
        time_closest_pair_algorithm);
    printf("TIME IN TOTAL:                                         %.2f\n\n",
        time_brute_force + time_closest_pair_algorithm);

    // Run tests.
    test(brute_force_pair, closest_points_pair);
    printf("All tests passed!\n");

    // Housekeeping.
    delete brute_force_pair;
    delete closest_points_pair;
    free(points);
    return 0;
}

void test(Pair *brute_force_pair, Pair *closest_points_pair)
{
    assert(*brute_force_pair == *closest_points_pair);
}
