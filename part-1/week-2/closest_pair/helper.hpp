#include "Pair.hpp"
#include "Point.hpp"

#ifndef HELPER_HPP
#define HELPER_HPP

void sort_points(Point *points, int first, int last, char sort_by);
void merge(Point *points, int first, int middle, int last, char sort_by);
Pair *closest_pair(Point *points_x, Point *points_y, int first, int last);
Pair *closest_split_pair(Point *points_x, Point *points_y, int first, int last, double delta);
Pair *brute_force(Point *points, int n);

#endif