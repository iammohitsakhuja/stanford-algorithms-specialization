/**
 * Author: Mohit Sakhuja
 * Dated: 30/09/2018
 *
 * Represents a vertex of a graph.
 * Contains the list of all outgoing edges from the vertex.
 */

#ifndef VERTEX_HH
#define VERTEX_HH

#include <list>

#include "Edge.hh"

using namespace std;

class Vertex {
public:
    list<Edge> edges;

    Vertex(void) = default;
    void add_edge(int dest, int weight);
};

#endif