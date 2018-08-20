#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
    int x;
    int y;

    Point(int x, int y);
    Point(Point &point);
    void scan(void);
    void print(void);
    double get_distance_with(Point p2);
    bool operator==(Point p2);
};

#endif
