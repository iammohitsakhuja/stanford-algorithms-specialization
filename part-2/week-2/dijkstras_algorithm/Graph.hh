/**
 * Author: Mohit Sakhuja
 * Dated: 27/08/2018
 *
 * Represents a graph with n vertices.
 */

#ifndef GRAPH_HH
#define GRAPH_HH

#include "Vertex.hh"

class Graph {
private:
    // Number of vertices.
    int n;

    // Array of all vertices in the graph.
    Vertex *vertices;

public:
    // Creation/Deletion of a graph.
    Graph(int n);
    ~Graph(void);

    // Adds a weighted edge between two vertices of the graph.
    void add_edge(
        int tail, int head, int weight = 1, bool is_directed = false);

    // Helper function for debugging.
    void print(void);

    // Returns a list of distances from a source vertex to every other vertex.
    int *calculate_distances(int src);
};

#endif
