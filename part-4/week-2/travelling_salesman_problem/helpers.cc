#include <algorithm>
#include <cfloat>
#include <cmath>
#include <fstream>

#include "helpers.hh"

using namespace std;

vector<Point> load_points_from_file(char *file_name)
{
    // Open file for reading.
    ifstream file(file_name);
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", file_name);
        return vector<Point>(0);
    }

    // Get the number of points to be read.
    int num_points;
    file >> num_points;

    // Create an array to hold the points.
    vector<Point> points(num_points);

    // Read coordinates of points from the file.
    for (int i = 0; i < num_points; i++) {
        float x, y;
        file >> x >> y;

        points[i].x = x;
        points[i].y = y;
    }

    return points;
}

vector<vector<float>> create_dist_matrix(vector<Point> &points)
{
    // Create a matrix.
    vector<vector<float>> dist_matrix = vector<vector<float>>(points.size());

    for (int i = 0; i < points.size(); i++) {
        dist_matrix[i] = vector<float>(points.size());

        for (int j = 0; j < dist_matrix[i].size(); j++)
            // Calculate each distance.
            dist_matrix[i][j] = i == j
                ? 0
                : sqrt(pow(points[i].x - points[j].x, 2)
                      + pow(points[i].y - points[j].y, 2));
    }

    return dist_matrix;
}

float find_minimum_cost_tour(
    vector<vector<float>> &dist_matrix, vector<Point> &points)
{
    int num_points  = points.size();
    int num_subsets = 1 << num_points;

    // Create a 2D array, and initialize entries in it to FLT_MAX.
    vector<vector<float>> lookup_table(
        num_subsets, vector<float>(num_points, FLT_MAX));
    lookup_table[1][0] = 0; // Base case.

    for (int size = 2; size <= num_points; size++) {
        // Construct a string with `size` copies of 1.
        string mask_str(size, 1);
        // Right pad the masked string with appropriate number of 0s.
        mask_str.resize(num_points, 0);

        // For each permutation of the given masked string.
        do {
            // Discard the subsets that do not include the very first point.
            if (!mask_str[0])
                continue;

            // Calculate the bitmask for the current subset.
            int bitmask = 1;
            for (int i = 1; i < num_points; i++)
                if (mask_str[i])
                    bitmask = bitmask | 1 << i;

            // For every element of the given subset j, j != 0.
            for (int j = 1; j < num_points; j++) {
                if (((bitmask >> j) & 1) == 1) {

                    // Calculate the bitmask of the set: (subset - j).
                    int rev_bitmask = bitmask ^ (1 << j);

                    // For each k in the newly created subset, calculate the
                    // minimum cost.
                    float min_cost = FLT_MAX;
                    for (int k = 0; k < num_points; k++)
                        if (((rev_bitmask >> k) & 1) == 1)
                            min_cost = min(lookup_table[rev_bitmask][k]
                                    + dist_matrix[k][j],
                                min_cost);

                    lookup_table[bitmask][j] = min_cost;
                }
            }
        } while (prev_permutation(mask_str.begin(), mask_str.end()));
    }

    // Calculate the final minimum cost.
    float min_cost     = FLT_MAX;
    int   complete_set = num_subsets - 1;
    for (int j = 2; j < num_points; j++)
        min_cost
            = min(lookup_table[complete_set][j] + dist_matrix[j][0], min_cost);

    return min_cost;
}
