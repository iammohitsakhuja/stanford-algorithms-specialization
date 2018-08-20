#include <list>

#include "Vertex.hh"

using namespace std;

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
};
