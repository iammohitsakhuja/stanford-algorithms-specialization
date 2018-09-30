#include "Edge.hh"

Edge::Edge(int __dest, int __weight)
    : dest(__dest)
    , weight(__weight)
{
}

int Edge::get_dest(void)
{
    return this->dest;
}

int Edge::get_weight(void)
{
    return this->weight;
}

void Edge::update_weight(int __weight)
{
    this->weight = __weight;
}