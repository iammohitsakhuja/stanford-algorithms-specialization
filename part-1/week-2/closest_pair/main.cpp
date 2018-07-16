#include "Point.hpp"
#include "constants.hpp"
#include "helper.hpp"
#include <iostream>

using namespace std;

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

    // Printing.
    printf("Before sorting:\n");
    for (int i = 0; i < n; i++)
        points[i].print();

    // Create two copies for holding sorted points.
    Point *points_x = (Point *)malloc(n * sizeof(Point));
    Point *points_y = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++)
    {
        points_x[i] = points[i];
        points_y[i] = points[i];
    }

    // Sort the two lists of points.
    sort_points(points_x, 0, n - 1, SORT_BY_X);
    sort_points(points_y, 0, n - 1, SORT_BY_Y);

    // Printing.
    printf("\nAfter sorting by X coordinates:\n");
    for (int i = 0; i < n; i++)
        points_x[i].print();

    printf("\nAfter sorting by Y coordinates:\n");
    for (int i = 0; i < n; i++)
        points_y[i].print();

    free(points);
    free(points_x);
    free(points_y);
    return 0;
}