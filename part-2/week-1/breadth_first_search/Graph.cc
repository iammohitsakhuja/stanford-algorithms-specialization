#include <queue>

#include "Graph.hh"

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
    this->vertices[v].edges.push_front(w);
    this->vertices[w].edges.push_front(v);
}

void Graph::print(void)
{
    for (int i = 0; i < n; i++) {
        printf("%i -> ", i);
        for (int j : this->vertices[i].edges)
            printf("%i ", j);
        printf("\n");
    }
}

void Graph::bfs(int s)
{
    // Create a queue to hold each vertex.
    queue<int> vertices;

    // Mark the current vertex as visited and add it to the queue.
    this->vertices[s].is_visited = true;
    vertices.push(s);

    // Iterate over all the vertices in the queue.
    while (!vertices.empty()) {
        // Get the first vertex from the queue.
        int v = vertices.front();
        vertices.pop();

        printf("%i ", v);

        // Add each unvisited vertex w that v is connected to, to the queue.
        for (int w : this->vertices[v].edges) {
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                vertices.push(w);
            }
        }
    }
    printf("\n");
}