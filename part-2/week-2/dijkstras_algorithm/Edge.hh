/**
 * Author: Mohit Sakhuja
 * Dated: 27/08/2018
 *
 * Represents a directed edge of a vertex. Used for the adjacency list
 * representation of a directed weighted graph.
 */

#ifndef EDGE_HH
#define EDGE_HH

struct Edge {
    // The vertex that the edge is pointing towards.
    int head;

    // Distance of the head from the tail vertex.
    int weight;

    Edge(int head, int weight);
};

#endif
