#include "Point.hpp"
#include "constants.hpp"
#include "helper.hpp"
#include <iostream>

using namespace std;

double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    Point *points = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++)
        points[i].scan();

    // Create two copies for holding sorted points.
    Point *points_x = (Point *)malloc(n * sizeof(Point));
    Point *points_y = (Point *)malloc(n * sizeof(Point));

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_brute_force = 0.0, time_closest_pair_algorithm = 0.0;

    getrusage(RUSAGE_SELF, &before);
    Pair *brute_force_pair = brute_force(points, n);
    getrusage(RUSAGE_SELF, &after);
    time_brute_force = calculate(&before, &after);

    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < n; i++)
    {
        points_x[i] = points[i];
        points_y[i] = points[i];
    }
    // Sort the two lists of points.
    sort_points(points_x, 0, n - 1, SORT_BY_X);
    sort_points(points_y, 0, n - 1, SORT_BY_Y);
    Pair *closest_points_pair = closest_pair(points_x, points_y, n);
    getrusage(RUSAGE_SELF, &after);
    time_closest_pair_algorithm = calculate(&before, &after);

    printf("Brute force:\n");
    brute_force_pair->print();
    printf("\n");

    printf("Closest pair algorithm:\n");
    closest_points_pair->print();
    printf("\n");

    // Test the correctness.
    *brute_force_pair == *closest_points_pair ? printf("Equal\n") : printf("Not equal\n");

    printf("TIME IN calculating result by brute force:             %.2f\n", time_brute_force);
    printf("TIME IN calculating result by closest pair algorithm:  %.2f\n", time_closest_pair_algorithm);
    printf("TIME IN TOTAL:                                         %.2f\n\n", time_brute_force + time_closest_pair_algorithm);

    delete brute_force_pair;
    delete closest_points_pair;
    free(points);
    free(points_x);
    free(points_y);
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
