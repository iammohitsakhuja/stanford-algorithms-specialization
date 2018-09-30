/**
 * Author: Mohit Sakhuja
 * Dated: 30/09/2018
 *
 * Represents a directed-weighted graph.
 */

#ifndef GRAPH_HH
#define GRAPH_HH

#include <vector>

#include "CycleExistsException.hh"
#include "Vertex.hh"

using namespace std;

class Graph {
private:
    int     num_vertices;
    Vertex *vertices;

    vector<int> get_vertex_weights(void);
    vector<int> bellman_ford_algorithm(int src);
    vector<int> dijkstras_algorithm(int src);

public:
    Graph(int __num_vertices);
    void add_edge(int src, int dest, int weight);

    // Helper function to print the graph.
    void print(void);

    vector<vector<int>> johnsons_algorithm(void);
};

#endif