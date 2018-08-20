#include "Point.hh"
#include <cmath>
#include <iostream>

Point::Point(int x, int y)
    : x(x)
    , y(y)
{
}

Point::Point(Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

void Point::scan(void)
{
    scanf("%i", &this->x);
    scanf("%i", &this->y);
}

void Point::print(void)
{
    printf("(%4i, %4i)\n", this->x, this->y);
}

double Point::get_distance_with(Point p2)
{
    return sqrt(pow(this->x - p2.x, 2) + pow(this->y - p2.y, 2));
}

bool Point::operator==(Point p2)
{
    if (this->x == p2.x && this->y == p2.y)
        return true;

    return false;
}
