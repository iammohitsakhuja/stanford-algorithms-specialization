#include "Point.hpp"
#include <iostream>

Point::Point(int x, int y) : x(x), y(y) {}

void Point::scan(void)
{
    scanf("%i", &this->x);
    scanf("%i", &this->y);
}

void Point::print(void)
{
    printf("(%2i, %2i)\n", this->x, this->y);
}
