#include "Vertex.hh"

Vertex::Vertex(bool is_visited)
{
    this->is_visited = is_visited;
}

Vertex::~Vertex(void)
{
    while (!this->edges.empty())
        this->edges.pop_front();
}
