#include <list>
#include <vector>

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
    vector<list<int>> find_connected_components(void);
};

#endif
