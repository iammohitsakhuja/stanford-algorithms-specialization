#include <algorithm>
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

void Graph::add_edge(int tail, int head, bool is_directed)
{
    // Adjust for indexing.
    tail--;
    head--;

    // Add edge(s).
    this->vertices[tail].edges.push_front(head);
    if (!is_directed)
        this->vertices[head].edges.push_front(tail);
}

void Graph::print(void)
{
    for (int i = 0; i < this->n; i++) {
        printf("%i -> ", i + 1);
        for (int j : this->vertices[i].edges)
            printf("%i ", j + 1);
        printf("\n");
    }
}

list<int> Graph::bfs(int source, bool set_unvisited)
{
    if (set_unvisited) {
        // Mark all the vertices as unvisited.
        for (int i = 0; i < this->n; i++)
            this->vertices[i].is_visited = false;
    }

    // Create a queue to hold each vertex.
    queue<int> vertices;

    // List to hold all vertices.
    list<int> traversed_vertices;

    // Mark the current vertex as visited and add it to the queue.
    this->vertices[source - 1].is_visited = true;
    vertices.push(source - 1);

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

    if (set_unvisited) {
        // Mark traversed vertices as unvisited again.
        for (int i : traversed_vertices)
            this->vertices[i - 1].is_visited = false;
    }

    return traversed_vertices;
}

int Graph::get_shortest_path(int src, int dest)
{
    if (src == dest)
        return 0;

    // Make sure all vertices are unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Adjust for indexing.
    src--;
    dest--;

    // Create a queue to hold each vertex.
    queue<int> vertices;

    // Create an array to hold distances.
    int *distances = (int *)malloc(this->n * sizeof(int));

    // Mark the current vertex as visited and add it to the queue.
    this->vertices[src].is_visited = true;
    distances[src]                 = 0;
    vertices.push(src);

    int distance = -1;

    // Iterate over all the vertices in the queue.
    while (!vertices.empty()) {
        // Get the vertex at the front of the queue.
        int v = vertices.front();
        vertices.pop();

        // Check if this is the vertex to be found.
        if (v == dest) {
            distance = distances[v];
            break;
        }

        // Add each unvisited vertex w that v is connected to, to the queue.
        for (int w : this->vertices[v].edges) {
            if (!this->vertices[w].is_visited) {
                this->vertices[w].is_visited = true;
                distances[w]                 = distances[v] + 1;
                vertices.push(w);
            }
        }
    }

    // Mark all vertices as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Remove any remaining elements from the queue (when vertex was found).
    while (!vertices.empty())
        vertices.pop();

    // Housekeeping.
    free(distances);

    return distance;
}

list<list<int>> Graph::find_connected_components(void)
{
    // Make sure all vertices are unvisited at first.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Create a list to store each list of connected components.
    list<list<int>> connected_components;

    // Compute each connected component.
    for (int i = 0; i < this->n; i++)
        if (!this->vertices[i].is_visited)
            connected_components.push_back(this->bfs(i + 1));

    // Mark all vertices as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    return connected_components;
}

list<int> Graph::dfs(int source, bool set_unvisited)
{
    if (set_unvisited) {
        // Mark all the vertices as unvisited.
        for (int i = 0; i < this->n; i++)
            this->vertices[i].is_visited = false;
    }

    // Create a stack to hold each vertex.
    stack<int> vertices;

    // List to hold all vertices.
    list<int> traversed_vertices;

    // Mark the current vertex as visited and add it to the stack.
    this->vertices[source - 1].is_visited = true;
    vertices.push(source - 1);

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

    if (set_unvisited) {
        // Mark traversed vertices as unvisited again.
        for (int i : traversed_vertices)
            this->vertices[i - 1].is_visited = false;
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
            sorted_vertices.splice(sorted_vertices.begin(), this->dfs(i + 1));

    // Mark all the nodes as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    return sorted_vertices;
}

Graph Graph::create_reverse_graph(void)
{
    // Create a new graph.
    Graph G(this->n);

    // Iterate over all vertices.
    for (int i = 0; i < this->n; i++)
        // Original edge is from i to w.
        for (int w : this->vertices[i].edges)
            // Reversed edge will be from w to i.
            G.vertices[w].edges.push_front(i);

    return G;
}

void Graph::reverse_graph(void)
{
    // Create a new graph.
    Graph G(this->n);

    // Iterate over all vertices.
    for (int i = 0; i < this->n; i++)
        // Original edge is from i to w.
        for (int w : this->vertices[i].edges)
            // Reversed edge will be from w to i.
            G.vertices[w].edges.push_front(i);

    // Swap all edge lists of this graph with the actual graph.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].edges.swap(G.vertices[i].edges);
}

list<list<int>> Graph::compute_scc(void)
{
    // Mark all vertices as unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Reverse the graph.
    this->reverse_graph();

    // Store all vertices in topological order. This will sort them in a way
    // that the vertex with highest f_value will be at the front of the list,
    // and the vertex with the lowest f_value will be at the end of the list.
    list<int> sorted_vertices = this->topological_sort();

    // Now, revert back to the original graph.
    this->reverse_graph();

    // Create a list to hold each strongly connected component.
    list<list<int>> strongly_connected_components;

    // Iterate over all vertices in the order of decreasing f_values.
    while (!sorted_vertices.empty()) {
        // Get the vertex with the (currently) highest f_value.
        int v = sorted_vertices.front();
        sorted_vertices.pop_front();

        // Adjust for indexing, and get the SCC for the current vertex.
        if (!this->vertices[v - 1].is_visited)
            strongly_connected_components.push_back(this->dfs(v));
    }

    // Set all vertices as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    return strongly_connected_components;
}

/**
 * Function to test whether one graph is the reverse of another graph.
 */
bool Graph::is_reverse_of(Graph &G)
{
    // Calculate the reverse of the current graph.
    // Test if the two graphs are equal.
    Graph reversed_G = this->create_reverse_graph();

    return reversed_G == G;
}

/**
 * Function to test whether two graphs are equal.
 */
bool Graph::operator==(Graph &G)
{
    // If number of vertices is not same, return false.
    if (this->n != G.n)
        return false;

    // Iterate over all vertices.
    for (int i = 0; i < this->n; i++) {
        // If the number of edges for each vertex is not the same, return
        // false.
        int size1 = this->vertices[i].edges.size();
        int size2 = G.vertices[i].edges.size();
        if (size1 != size2)
            return false;

        // List items may be in a different order. Hence, create two arrays to
        // hold the elements.
        int *array1 = (int *)malloc(size1 * sizeof(int));
        int *array2 = (int *)malloc(size2 * sizeof(int));

        // Iterate over both lists of edges, and add items to the respective
        // arrays.
        list<int>::iterator it1 = this->vertices[i].edges.begin();
        list<int>::iterator it2 = G.vertices[i].edges.begin();

        for (int i = 0; it1 != this->vertices[i].edges.end()
             && it2 != G.vertices[i].edges.end() && i < size1 && i < size2;
             i++, it1++, it2++) {
            array1[i] = *it1;
            array2[i] = *it2;
        }

        // Sort the arrays.
        sort(array1, array1 + size1);
        sort(array2, array2 + size2);

        // Compare the array items.
        for (int i = 0; i < size1; i++)
            if (array1[i] != array2[i])
                return false;

        // Housekeeping.
        free(array1);
        free(array2);
    }

    return true;
}
