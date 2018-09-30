#include "Vertex.hh"

void Vertex::add_edge(int dest, int weight)
{
    this->edges.push_back(Edge(dest, weight));
}