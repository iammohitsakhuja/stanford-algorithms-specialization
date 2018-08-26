/**
 * Author: Mohit Sakhuja
 * Dated: 26/08/2018
 *
 * This header file contains the declaration of a struct representing a vertex
 * of a graph. Each vertex contains information regarding whether it has been
 * visited before or not, and a list of edges to all the other vertices that
 * it is connected to.
 */

#ifndef VERTEX_HH
#define VERTEX_HH

#include <list>

using namespace std;

struct Vertex {
    bool is_visited;
    list<int> edges;

    Vertex(bool is_visited = false);
    ~Vertex(void);
};

#endif
