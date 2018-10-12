/**
 * Author: Mohit Sakhuja
 * Dated: 12/10/2018
 *
 * Contains declarations for helper functions needed for the TSP problem.
 */

#ifndef HELPERS_HH
#define HELPERS_HH

#include <vector>

#include "Point.hh"

using namespace std;

vector<Point>         load_points_from_file(char *file_name);
vector<vector<float>> create_dist_matrix(vector<Point> &points);
float                 find_minimum_cost_tour(
                    vector<vector<float>> &dist_matrix, vector<Point> &points);

#endif