#include <queue>

#include "Graph.hh"

using namespace std;

Graph::Graph(int n)
{
    this->n        = n;
    this->vertices = new Vertex[n];
}

Graph::~Graph(void)
{
    delete[] this->vertices;
}

void Graph::add_edge(int v, int w)
{
    // Adjust for indexing.
    v--;
    w--;

    // Add undirected edge.
    this->vertices[v].edges.push_front(w);
    this->vertices[w].edges.push_front(v);
}

void Graph::print(void)
{
    for (int i = 0; i < n; i++) {
        printf("%i -> ", i + 1);
        for (int j : this->vertices[i].edges)
            printf("%i ", j + 1);
        printf("\n");
    }
}

int Graph::get_shortest_path(int src, int dest)
{
    if (src == dest)
        return 0;

    // Adjust for indexing.
    src--;
    dest--;

    // Create a queue to hold each vertex.
    queue<int> vertices;

    // Mark the current vertex as visited and add it to the queue.
    this->vertices[src].is_visited = true;
    this->vertices[src].distance   = 0;
    vertices.push(src);

    int distance;
    bool vertex_found = false;

    // Iterate over all the vertices in the queue.
    while (!vertices.empty()) {
        // Get the vertex at the front of the queue.
        int v = vertices.front();
        vertices.pop();

        // Check if this is the vertex to be found.
        if (v == dest) {
            vertex_found = true;
            distance     = this->vertices[v].distance;
            break;
        }

        // Add each unvisited vertex w that v is connected to, to the queue.
        for (int w : this->vertices[v].edges) {
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                this->vertices[w].distance   = this->vertices[v].distance + 1;
                vertices.push(w);
            }
        }
    }

    // Mark all vertices as unvisited again.
    for (int i = 0; i < n; i++) {
        this->vertices[i].is_visited = false;
        this->vertices[i].distance   = 0;
    }

    // Remove any remaining elements from the queue (when vertex was found).
    while (!vertices.empty())
        vertices.pop();

    if (!vertex_found)
        return -1;

    return distance;
}
