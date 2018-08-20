#include <list>

#include "Vertex.hh"

using namespace std;

#ifndef GRAPH_HH
#define GRAPH_HH

class Graph {
private:
    // Number of vertices.
    int n;
    Vertex *vertices;

public:
    Graph(int n);
    ~Graph(void);
    void add_edge(int v, int w);
    void print(void);
    list<int> bfs(int s);
    list<int> dfs(int s);
};

#endif
