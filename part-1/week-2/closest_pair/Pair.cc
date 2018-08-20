#include "Pair.hh"
#include "Point.hh"
#include <iostream>

Pair::Pair(Point p1, Point p2)
    : p1(p1)
    , p2(p2)
{
    this->distance = p1.get_distance_with(p2);
}

void Pair::print(void)
{
    printf("Pair: ((%4i, %4i), (%4i, %4i))\n", this->p1.x, this->p1.y,
        this->p2.x, this->p2.y);
}

bool Pair::operator==(Pair pair2)
{
    if ((this->p1 == pair2.p1 && this->p2 == pair2.p2)
        || (this->p1 == pair2.p2 && this->p2 == pair2.p1))
        return true;

    return false;
}
