#include <list>

#include "Vertex.hh"

using namespace std;

#ifndef GRAPH_HH
#define GRAPH_HH

class Graph {
private:
    // Number of vertices.
    int n;
    // Array of all vertices in the graph.
    Vertex *vertices;

    // Helper function for topological sort.
    list<int> topological_sort_util(int s);

public:
    // Memory management.
    Graph(int n);
    ~Graph(void);

    // Add an undirected edge between v and w.
    void add_undirected_edge(int v, int w);

    // Add a directed edge from tail to head.
    void add_directed_edge(int tail, int head);

    // Helper function for debugging.
    void print(void);

    // Traversing the graph.
    list<int> bfs(int s);
    list<int> dfs(int s);

    // Topological sort.
    list<int> topological_sort(void);
};

#endif
