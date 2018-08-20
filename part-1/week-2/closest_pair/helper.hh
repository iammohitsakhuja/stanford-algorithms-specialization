#include "Pair.hh"
#include "Point.hh"

#ifndef HELPER_HPP
#define HELPER_HPP

void sort_points(Point *points, int first, int last, char sort_by);
void merge(Point *points, int first, int middle, int last, char sort_by);
Pair *find_closest_pair(Point *points, int n);
Pair *closest_pair(Point *points_x, Point *points_y, int n);
Pair *closest_split_pair(
    Point *points_x, Point *points_y, int n, double delta);
Pair *brute_force(Point *points, int n);

#endif
