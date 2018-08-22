#include <list>

using namespace std;

#ifndef VERTEX_HH
#define VERTEX_HH

struct Vertex {
    bool is_visited;
    list<int> edges;

    Vertex(bool is_visited = false);
    ~Vertex(void);
};

#endif
