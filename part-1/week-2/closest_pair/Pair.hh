#include "Point.hh"

#ifndef PAIR_HPP
#define PAIR_HPP

class Pair {
public:
    Point p1;
    Point p2;
    double distance;

    Pair(Point p1, Point p2);
    void print(void);
    bool operator==(Pair pair2);
};

#endif
