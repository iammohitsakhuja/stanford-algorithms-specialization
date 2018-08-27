/**
 * Author: Mohit Sakhuja
 * Dated: 27/08/2018
 *
 * Represents a vertex of a graph that is connected to other vertices which
 * are represented in the form of a list of edges.
 */

#ifndef VERTEX_HH
#define VERTEX_HH

#include <list>

#include "Edge.hh"

using namespace std;

struct Vertex {
    bool is_visited;
    list<Edge> edges;

    Vertex(bool is_visited = false);
    ~Vertex(void);
};

#endif
