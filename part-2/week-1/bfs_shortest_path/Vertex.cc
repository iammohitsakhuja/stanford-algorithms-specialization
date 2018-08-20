#include "Vertex.hh"

Vertex::Vertex(bool is_visited)
{
    this->is_visited = is_visited;
    this->distance   = 0;
}

Vertex::~Vertex(void)
{
    while (!this->edges.empty())
        this->edges.pop_front();
}
