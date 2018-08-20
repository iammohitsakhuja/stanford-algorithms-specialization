#include "helper.hh"
#include "Point.hh"
#include "constants.hh"
#include <cmath>
#include <iostream>

void sort_points(Point *points, int first, int last, char sort_by)
{
    if (sort_by != SORT_BY_X && sort_by != SORT_BY_Y) {
        fprintf(stderr, "Error. Invalid sort argument.\n");
        return;
    }

    if (first == last)
        return;

    int middle = (first + last) / 2;

    // Sort the left subarray of points.
    sort_points(points, first, middle, sort_by);

    // Sort the right subarray of points.
    sort_points(points, middle + 1, last, sort_by);

    // Merge the two subarrays.
    merge(points, first, middle, last, sort_by);
}

void merge(Point *points, int first, int middle, int last, char sort_by)
{
    // Create 2 new arrays to hold the existing elements.
    int left_len  = middle - first + 1;
    int right_len = last - middle;

    Point *left_array  = (Point *)malloc(left_len * sizeof(Point));
    Point *right_array = (Point *)malloc(right_len * sizeof(Point));

    // Copy the existing points into these 2 arrays.
    for (int i = 0; i < left_len; i++)
        left_array[i] = points[first + i];

    for (int j = 0; j < right_len; j++)
        right_array[j] = points[middle + 1 + j];

    // Merge the 2 subarrays according to the order specified.
    int i = 0;
    int j = 0;
    int k = first;
    if (sort_by == SORT_BY_X)
        while (i < left_len && j < right_len) {
            if (left_array[i].x < right_array[j].x)
                points[k++] = left_array[i++];
            else
                points[k++] = right_array[j++];
        }
    else /* If numbers are to be sorted by their x-coordinate. */
        while (i < left_len && j < right_len) {
            if (left_array[i].y < right_array[j].y)
                points[k++] = left_array[i++];
            else
                points[k++] = right_array[j++];
        } /* Else, sort them by y-coordinate. */

    // Copy over the remaining elements, if any.
    while (i < left_len)
        points[k++] = left_array[i++];

    while (j < right_len)
        points[k++] = right_array[j++];

    // Free the 2 subarrays.
    free(left_array);
    free(right_array);
}

Pair *find_closest_pair(Point *points, int n)
{
    // Create 2 arrays for holding the points sorted by their
    // x and y coordinates.
    Point *points_x = (Point *)malloc(n * sizeof(Point));
    Point *points_y = (Point *)malloc(n * sizeof(Point));

    // Copy the points into the 2 arrays.
    for (int i = 0; i < n; i++) {
        points_x[i] = points[i];
        points_y[i] = points[i];
    }

    // Sort the two lists of points.
    sort_points(points_x, 0, n - 1, SORT_BY_X);
    sort_points(points_y, 0, n - 1, SORT_BY_Y);

    // Find the closest pair.
    Pair *closest_points_pair = closest_pair(points_x, points_y, n);

    // Housekeeping.
    free(points_x);
    free(points_y);

    return closest_points_pair;
}

Pair *closest_pair(Point *points_x, Point *points_y, int n)
{
    // Just solve using brute force when n <= 3.
    if (n <= 3)
        return brute_force(points_x, n);

    // Divide the x and y arrays into two halves each.
    int middle    = (n - 1) / 2;
    int left_len  = (n + 1) / 2;
    int right_len = n / 2;

    // x becomes qx and rx.
    // y becomes qy and ry.
    Point *qx = (Point *)malloc(left_len * sizeof(Point));
    Point *qy = (Point *)malloc(left_len * sizeof(Point));
    Point *rx = (Point *)malloc(right_len * sizeof(Point));
    Point *ry = (Point *)malloc(right_len * sizeof(Point));

    // Divide the x array normally.
    for (int i = 0; i < left_len; i++)
        qx[i] = points_x[i];

    for (int j = 0; j < right_len; j++)
        rx[j] = points_x[middle + 1 + j];

    // The y array should be divided using the midpoint of x array.
    // This process assumes that each point has a unique x-coordinate.
    Point midpoint = points_x[middle];

    int j = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        // Add point to qy if it lies in the left half of points_x.
        if (points_y[i].x <= midpoint.x)
            qy[j++] = points_y[i];
        // Else, add it to ry.
        else
            ry[k++] = points_y[i];
    }

    // Find the closest pairs in the left and right halves recursively.
    Pair *pair1 = closest_pair(qx, qy, left_len);
    Pair *pair2 = closest_pair(rx, ry, right_len);

    // Cleanup.
    free(qx);
    free(qy);
    free(rx);
    free(ry);

    // Find the closest pair that has one point in one half,
    // and the other point in the other half.
    double delta = std::min(pair1->distance, pair2->distance);
    Pair *pair3  = closest_split_pair(points_x, points_y, n, delta);

    // Return the appropriate pair.
    if (pair3 != NULL) {
        delete pair1;
        delete pair2;
        return pair3;
    } /* If the closest pair is a split pair. */
    else {
        if (pair1->distance < pair2->distance) {
            delete pair2;
            return pair1;
        } else {
            delete pair1;
            return pair2;
        }
    } /* Else if the closest pair is in one of the two halves. */
}

Pair *closest_split_pair(Point *points_x, Point *points_y, int n, double delta)
{
    int middle     = (n - 1) / 2;
    Point midpoint = points_x[middle];

    // Calculate the number of points that have their x-coordinate in the
    // range [x - delta, x + delta], sorted by y-coordinate.
    int count = 0;
    for (int i = 0; i < n; i++)
        if (abs(points_y[i].x - midpoint.x) < delta)
            count++;

    // Get those points into a separate array.
    Point *sy = (Point *)malloc(count * sizeof(Point));
    for (int i = 0, index = 0; i < n; i++)
        if (abs(points_y[i].x - midpoint.x) < delta)
            sy[index++] = points_y[i];

    // Find the closest pair.
    // The inner loop will only run a max of 7 times for each iteration
    // of the outer loop.
    Pair *pair      = new Pair(sy[0], sy[1]);
    bool pair_found = false; /* New pair has to be the closest pair */
    for (int i = 0, i_len = count - 2; i <= i_len; i++)
        for (int j = i + 1, j_len = std::min(i + 7, count - 1); j <= j_len;
             j++) {
            double distance = sy[i].get_distance_with(sy[j]);
            if (distance < delta) {
                /* Closest pair has been found */
                pair_found = true;
                if (distance < pair->distance) {
                    pair->p1       = sy[i];
                    pair->p2       = sy[j];
                    pair->distance = distance;
                }
            }
        }

    // If the pair found was not the closest pair, then return NULL.
    if (!pair_found) {
        delete pair;
        return NULL;
    }

    return pair;
}

Pair *brute_force(Point *points, int n)
{
    // Create a new pair to hold the pair with least distance.
    Pair *pair = new Pair(points[0], points[1]);

    // Find the closest pair by calculating the distance between each pair of
    // points. O(n^2).
    for (int i = 0, length = n - 1; i < length; i++) {
        for (int j = i + 1; j < n; j++) {
            double distance = points[i].get_distance_with(points[j]);
            if (distance < pair->distance) {
                pair->p1       = points[i];
                pair->p2       = points[j];
                pair->distance = distance;
            }
        }
    }

    return pair;
}
