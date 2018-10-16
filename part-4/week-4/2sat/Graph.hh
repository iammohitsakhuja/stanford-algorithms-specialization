/**
 * Author: Mohit Sakhuja
 * Dated: 15/10/2018
 *
 * Represents a directed graph.
 */

#ifndef GRAPH_HH
#define GRAPH_HH

#include "Vertex.hh"

struct Graph {
    int     num_vertices;
    Vertex *vertices;

    Graph(int num_vertices);
    void        add_edge(int src, int dest);
    Graph *     create_reverse_graph(void);
    vector<int> get_topological_sorting(void);
    void        dfs(int src, vector<int> &topologically_sorted_vertices,
               bool set_unvisited = false);
    vector<int> compute_sccs(void);

    void print(void);
};

#endif
