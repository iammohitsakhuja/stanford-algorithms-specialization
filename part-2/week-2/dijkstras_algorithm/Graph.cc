#include <queue>

#include "Graph.hh"
#include "HeapNode.hh"

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

void Graph::add_edge(int tail, int head, int weight, bool is_directed)
{
    // Adjust for indexing.
    tail--;
    head--;

    // Create an edge.
    Edge edge(head, weight);

    // Add the edge to the respective vertex's list of edges.
    this->vertices[tail].edges.push_front(edge);
    if (!is_directed) {
        Edge edge(tail, weight);
        this->vertices[head].edges.push_front(edge);
    }
}

void Graph::print(void)
{
    for (int i = 0; i < this->n; i++) {
        printf("%i -> ", i + 1);
        for (Edge edge : this->vertices[i].edges)
            printf("%i,%i ", edge.head + 1, edge.weight);
        printf("\n");
    }
}

int *Graph::calculate_distances(int src)
{
    // Adjust for indexing.
    src--;

    // Mark all vertices as unvisited.
    for (int i = 0; i < this->n; i++)
        this->vertices[i].is_visited = false;

    // Initialize all distances.
    int *distances = new int[this->n];
    for (int i = 0; i < this->n; i++)
        if (i != src)
            distances[i] = 1000000;

    // Custom lambda function for comparisons.
    auto comparator
        = [](HeapNode &a, HeapNode &b) { return a.distance > b.distance; };

    // Create a min heap to store vertices sorted by their distance to the
    // set of vertices that has been processed.
    priority_queue<HeapNode, vector<HeapNode>, decltype(comparator)> heap(
        comparator);

    // Add all vertices to heap, along with their distances from the source.
    for (int i = 0; i < this->n; i++)
        heap.push(HeapNode(i, distances[i]));

    // Maintain count of stored vertices.
    int count = 0;
    while (count != this->n) {
        // Extract the node from the heap with minimum distance from the set of
        // processed vertices.
        HeapNode node = heap.top();
        heap.pop();

        // Only process vertices that have not yet been visited.
        if (!this->vertices[node.vertex].is_visited) {
            // Mark this vertex as processed.
            this->vertices[node.vertex].is_visited = true;

            // For each of the unvisited vertices that this vertex points
            // towards, calculate Dijkstra's greedy distance, and accordingly
            // add them to the heap.
            for (Edge edge : this->vertices[node.vertex].edges)
                if (!this->vertices[edge.head].is_visited) {
                    int distance = node.distance + edge.weight;
                    if (distance < distances[edge.head]) {
                        heap.push(HeapNode(edge.head, distance));
                        distances[edge.head] = distance;
                    }
                }

            count++;
        }
    }

    // Remove any remaining elements from the heap.
    while (!heap.empty())
        heap.pop();

    // Mark all vertices as unvisited again.
    for (int i = 0; i < this->n; i++)
        this->vertices[i] = false;

    return distances;
}
