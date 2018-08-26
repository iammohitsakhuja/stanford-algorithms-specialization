/**
 * Author: Mohit Sakhuja
 * Dated: 26/08/2018
 *
 * This header file contains the declaration of a class representing a Graph.
 * The graph is represented using an adjacency list. The graph may be
 * directed or undirected. It can have multiple operations - traversing using
 * bfs and dfs, sorting vertices topologically, reversing the directed edges,
 * computing connected components, shortest path and strictly connected
 * components.
 */

#ifndef GRAPH_HH
#define GRAPH_HH

#include "Vertex.hh"

using namespace std;

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

    // Add an edge between tail and head.
    void add_edge(int tail, int head, bool is_directed = false);

    // Helper function for debugging.
    void print(void);

    // Traversing the graph.
    list<int> bfs(int source, bool set_unvisited = false);
    list<int> dfs(int source, bool set_unvisited = false);

    // Shortest path.
    int get_shortest_path(int src, int dest);

    // Find connected components.
    list<list<int>> find_connected_components(void);

    // Topological sort.
    list<int> topological_sort(void);

    // Reverse graph.
    Graph create_reverse_graph(void);
    void reverse_graph(void);

    // Gives SCCs.
    list<list<int>> compute_scc(void);

    // Tests.
    bool test_is_reverse(Graph &G);
    bool operator==(Graph &G);
};

#endif
