#include "Pair.hpp"
#include "Point.hpp"
#include <iostream>

Pair::Pair(Point p1, Point p2) : p1(p1), p2(p2)
{
    this->distance = p1.get_distance_with(p2);
}

void Pair::print(void)
{
    printf("Pair:\n");
    printf("\t(%4i, %4i)\n", this->p1.x, this->p1.y);
    printf("\t(%4i, %4i)\n", this->p2.x, this->p2.y);
}