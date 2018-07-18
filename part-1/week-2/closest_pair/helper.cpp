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
    else
    {
        int middle = (first + last) / 2;

        // Sort the left subarray of points.
        sort_points(points, first, middle, sort_by);

        // Sort the right subarray of points.
        sort_points(points, middle + 1, last, sort_by);

        // Merge the two subarrays.
        merge(points, first, middle, last, sort_by);

        return;
    }
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

Pair *closest_pair(Point *points_x, Point *points_y, int first, int last)
{
    int n = last - first + 1;
    if (n < 4)
    {
        Pair *pair = new Pair(points_x[0], points_x[1]);
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                double distance = points_x[i].get_distance_with(points_x[j]);
                if (distance < pair->distance)
                {
                    pair->p1 = points_x[i];
                    pair->p2 = points_x[j];
                    pair->distance = distance;
                }
            }
        }

        return pair;
    }
    else
    {
        Point *qx = (Point *)malloc((n / 2) * sizeof(Point));
        Point *qy = (Point *)malloc((n / 2) * sizeof(Point));
        Point *rx = (Point *)malloc((n / 2) * sizeof(Point));
        Point *ry = (Point *)malloc((n / 2) * sizeof(Point));

        int middle = (last - first) / 2;
        for (int i = 0, length = n / 2; i < length; i++)
        {
            qx[i] = points_x[first + i];
            rx[i] = points_x[middle + 1 + i];
        }

        Point midpoint = points_x[middle];

        int j = 0;
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            if (points_y[first + i].x < midpoint.x)
            {
                qy[j] = points_y[first + i];
                j++;
            }
            else
            {
                ry[j] = points_y[first + i];
                k++;
            }
        }

        Pair *pair1 = closest_pair(qx, qy, first, middle);
        Pair *pair2 = closest_pair(rx, ry, middle + 1, last);

        // Cleanup.
        free(qx);
        free(qy);
        free(rx);
        free(ry);

        double delta = std::min(pair1->distance, pair2->distance);
        Pair *pair3 = closest_split_pair(points_x, points_y, first, last, delta);

        if (pair3 && pair3->distance < delta)
        {
            delete pair1;
            delete pair2;
            return pair3;
        }
        else
        {
            delete pair3;
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
}

Pair *closest_split_pair(Point *points_x, Point *points_y, int first, int last, double delta)
{
    int n = last - first + 1;
    int middle = (last - first) / 2;
    Point midpoint = points_x[middle];

    Point *Sy = (Point *)malloc(n * sizeof(Point));
    // Sy should be in decreasing order.
    int index = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (abs(points_y[i].x - midpoint.x) < delta)
        {
            Sy[index] = points_y[i];
            index++;
        }
    }
    int length_sy = index;

    Pair *pair = new Pair(Sy[0], Sy[1]);
    bool pair_found = false;
    for (int i = 0; i < length_sy; i++)
    {
        for (int j = i + 1, length = std::min(i + 15, length_sy); j < length; j++)
        {
            double distance = Sy[i].get_distance_with(Sy[j]);
            if (distance < delta && distance < pair->distance)
            {
                pair_found = true;
                pair->p1 = Sy[i];
                pair->p2 = Sy[j];
                pair->distance = distance;
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
