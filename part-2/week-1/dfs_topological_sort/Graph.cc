#include <queue>
#include <stack>

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

void Graph::add_undirected_edge(int v, int w)
{
    // Adjust for indexing.
    v--;
    w--;

    // Add undirected edge.
    this->vertices[v].edges.push_front(w);
    this->vertices[w].edges.push_front(v);
}

void Graph::add_directed_edge(int tail, int head)
{
    // Adjust for indexing.
    tail--;
    head--;

    // Add directed edge.
    this->vertices[tail].edges.push_front(head);
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

list<int> Graph::bfs(int s)
{
    // Mark all the vertices as unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Create a queue to hold each vertex.
    queue<int> vertices;

    // List to hold all vertices.
    list<int> traversed_vertices;

    // Mark the current vertex as visited and add it to the queue.
    this->vertices[s - 1].is_visited = true;
    vertices.push(s - 1);

    // Iterate over all the vertices in the queue.
    while (!vertices.empty()) {
        // Get the first vertex from the queue.
        int v = vertices.front();
        vertices.pop();
        traversed_vertices.push_back(v + 1);

        // Add each unvisited vertex w that v is connected to, to the queue.
        for (int w : this->vertices[v].edges)
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                vertices.push(w);
            }
    }

    // Mark all vertices as unvisited again.
    for (int i : traversed_vertices)
        this->vertices[i - 1].is_visited = false;

    return traversed_vertices;
}

list<int> Graph::dfs(int s)
{
    // Mark all the vertices as unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Create a stack to hold each vertex.
    stack<int> vertices;

    // List to hold all vertices.
    list<int> traversed_vertices;

    // Mark the current vertex as visited and add it to the stack.
    this->vertices[s - 1].is_visited = true;
    vertices.push(s - 1);

    // Iterate over all the vertices in the stack.
    while (!vertices.empty()) {
        // Get the top vertex from the stack.
        int v = vertices.top();
        vertices.pop();
        traversed_vertices.push_back(v + 1);

        // Add each unvisited vertex w that v is connected to, to the stack.
        for (int w : this->vertices[v].edges)
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                vertices.push(w);
            }
    }

    // Mark all vertices as unvisited again.
    for (int i : traversed_vertices)
        this->vertices[i - 1].is_visited = false;

    return traversed_vertices;
}

list<int> Graph::topological_sort_util(int s)
{
    // Create a stack to hold each vertex.
    stack<int> vertices;

    // List to hold all vertices.
    list<int> traversed_vertices;

    // Mark the current vertex as visited and add it to the stack.
    this->vertices[s - 1].is_visited = true;
    vertices.push(s - 1);

    // Iterate over all the vertices in the stack.
    while (!vertices.empty()) {
        // Get the top vertex from the stack.
        int v = vertices.top();
        vertices.pop();
        traversed_vertices.push_back(v + 1);

        // Add each unvisited vertex w that v is connected to, to the stack.
        for (int w : this->vertices[v].edges)
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                vertices.push(w);
            }
    }

    return traversed_vertices;
}

list<int> Graph::topological_sort(void)
{
    // First mark all the nodes as unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // List to hold all vertices.
    list<int> sorted_vertices;

    // Call DFS on each unvisited vertex.
    for (int i = 0; i < this->n; i++)
        if (!this->vertices[i].is_visited)
            // Apply DFS on each unvisited vertex, and push the list received
            // to the beginning of the complete list.
            sorted_vertices.splice(
                sorted_vertices.begin(), topological_sort_util(i + 1));

    // Mark all the nodes as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    return sorted_vertices;
}
