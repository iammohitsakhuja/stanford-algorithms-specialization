#include <list>

using namespace std;

struct Vertex {
    bool is_visited;
    list<int> edges;

    Vertex(bool is_visited = false);
    ~Vertex(void);
};