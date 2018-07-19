#include "helper.hpp"
#include "Point.hpp"
#include "constants.hpp"
#include <cmath>
#include <iostream>

void sort_points(Point *points, int first, int last, char sort_by)
{
    if (sort_by != SORT_BY_X && sort_by != SORT_BY_Y)
    {
        printf("Error. Invalid sort argument.\n");
        return;
    }

    if (first == last)
    {
        return;
    }

    int middle = (first + last) / 2;

    // Sort the left subarray of points.
    sort_points(points, first, middle, sort_by);

    // Sort the right subarray of points.
    sort_points(points, middle + 1, last, sort_by);

    // Merge the two subarrays.
    merge(points, first, middle, last, sort_by);

    return;
}

void merge(Point *points, int first, int middle, int last, char sort_by)
{
    // Copy the existing elements into new arrays.
    int left_len = middle - first + 1;
    int right_len = last - middle;

    Point *left_array = (Point *)malloc(left_len * sizeof(Point));
    Point *right_array = (Point *)malloc(right_len * sizeof(Point));

    for (int i = 0; i < left_len; i++)
        left_array[i] = points[first + i];

    for (int j = 0; j < right_len; j++)
        right_array[j] = points[middle + 1 + j];

    // Merge the two subarrays.
    int i = 0;
    int j = 0;
    int k = first;

    if (sort_by == SORT_BY_X)
    {
        while (i < left_len && j < right_len)
        {
            if (left_array[i].x < right_array[j].x)
            {
                points[k] = left_array[i];
                i++;
            }
            else
            {
                points[k] = right_array[j];
                j++;
            }
            k++;
        }
    }
    else
    {
        while (i < left_len && j < right_len)
        {
            if (left_array[i].y < right_array[j].y)
            {
                points[k] = left_array[i];
                i++;
            }
            else
            {
                points[k] = right_array[j];
                j++;
            }
            k++;
        }
    }

    // Copy the remaining elements.
    while (i < left_len)
    {
        points[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_len)
    {
        points[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

Pair *closest_pair(Point *points_x, Point *points_y, int n)
{
    // Just solve using brute force when n <=3.
    if (n < 4)
    {
        return brute_force(points_x, n);
    }

    // Divide the x and y arrays into two halves each.
    int middle = (n - 1) / 2;
    int left_len = (n + 1) / 2;
    int right_len = n / 2;

    Point *qx = (Point *)malloc(left_len * sizeof(Point));
    Point *qy = (Point *)malloc(left_len * sizeof(Point));
    Point *rx = (Point *)malloc(right_len * sizeof(Point));
    Point *ry = (Point *)malloc(right_len * sizeof(Point));

    for (int i = 0; i < left_len; i++)
        qx[i] = points_x[i];

    for (int j = 0; j < right_len; j++)
        rx[j] = points_x[middle + 1 + j];

    // The y array should be divided using the midpoint of x array.
    Point midpoint = points_x[middle];

    int j = 0;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (points_y[i].x <= midpoint.x)
        {
            qy[j] = points_y[i];
            j++;
        }
        else
        {
            ry[k] = points_y[i];
            k++;
        }
    }

    // Find the closest pairs in the left and right halves.
    Pair *pair1 = closest_pair(qx, qy, left_len);
    Pair *pair2 = closest_pair(rx, ry, right_len);

    // Cleanup.
    free(qx);
    free(qy);
    free(rx);
    free(ry);

    // Find the closest pair in both halves.
    double delta = std::min(pair1->distance, pair2->distance);
    Pair *pair3 = closest_split_pair(points_x, points_y, n, delta);

    // Return the appropriate pair.
    if (pair3 != NULL)
    {
        delete pair1;
        delete pair2;
        return pair3;
    }
    else
    {
        if (pair1->distance < pair2->distance)
        {
            delete pair2;
            return pair1;
        }
        else
        {
            delete pair1;
            return pair2;
        }
    }

}

Pair *closest_split_pair(Point *points_x, Point *points_y, int n, double delta)
{
    int middle = (n - 1) / 2;
    Point midpoint = points_x[middle];

    // Calculate the number of points that have their x-coordinate in [x - delta, x + delta],
    // sorted by y-coordinate.
    int count = 0;
    for (int i = 0; i < n; i++)
        if (abs(points_y[i].x - midpoint.x) < delta)
            count++;

    // Get those points into a separate array.
    Point *sy = (Point *)malloc(count * sizeof(Point));
    for (int i = 0, index = 0; i < n; i++)
        if (abs(points_y[i].x - midpoint.x) < delta)
        {
            sy[index] = points_y[i];
            index++;
        }

    // Find the closest pair.
    // The inner loop will only run a max of 7 times for each iteration of the outer loop.
    Pair *pair = new Pair(sy[0], sy[1]);
    bool pair_found = false;
    for (int i = 0, i_len = count - 2; i <= i_len; i++)
    {
        for (int j = i + 1, j_len = std::min(i + 7, count - 1); j <= j_len; j++)
        {
            double distance = sy[i].get_distance_with(sy[j]);
            if (distance < delta)
            {
                pair_found = true;
                if (distance < pair->distance)
                {
                    pair->p1 = sy[i];
                    pair->p2 = sy[j];
                    pair->distance = distance;
                }
            }
        }
    }

    if (!pair_found)
    {
        delete pair;
        return NULL;
    }

    return pair;
}

Pair *brute_force(Point *points, int n)
{
    // Create a new pair to hold the pair with least distance.
    Pair *pair = new Pair(points[0], points[1]);
    for (int i = 0, length = n - 1; i < length; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double distance = points[i].get_distance_with(points[j]);
            if (distance < pair->distance)
            {
                pair->p1 = points[i];
                pair->p2 = points[j];
                pair->distance = distance;
            }
        }
    }

    return pair;
}
