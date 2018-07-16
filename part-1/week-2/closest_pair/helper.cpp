#include "helper.hpp"
#include "Point.hpp"
#include "constants.hpp"
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