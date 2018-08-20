#include "Vertex.hh"

#ifndef GRAPH_HH
#define GRAPH_HH

class Graph {
private:
    int n;
    Vertex *vertices;

public:
    Graph(int n);
    ~Graph(void);
    void add_edge(int v, int w);
    void print(void);
    int get_shortest_path(int src, int dest);
};

#endif
