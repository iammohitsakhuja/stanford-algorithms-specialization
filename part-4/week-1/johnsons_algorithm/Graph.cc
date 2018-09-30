#include <cstdlib>
#include <queue>

#include "Graph.hh"
#include "HeapNode.hh"

Graph::Graph(int __num_vertices)
    : num_vertices(__num_vertices)
{
    this->vertices = new Vertex[__num_vertices];
}

void Graph::add_edge(int src, int dest, int weight)
{
    // Adjust for indexing.
    src--;
    dest--;

    // Add edge to the appropriate vertex.
    this->vertices[src].add_edge(dest, weight);
}

void Graph::print(void)
{
    for (int i = 0; i < this->num_vertices; i++) {
        printf("%i -> ", i + 1);
        for (Edge edge : this->vertices[i].edges)
            printf("(%i, %i) ", edge.get_dest() + 1, edge.get_weight());
        printf("\n");
    }
}

vector<vector<int>> Graph::johnsons_algorithm(void)
{
    // Get the vertex weights required to transform the graph.
    vector<int> vertex_weights = this->get_vertex_weights();

    // Update the edge weights of the graph with the new weights.
    for (int i = 0; i < this->num_vertices; i++) {
        for (list<Edge>::iterator edge = this->vertices[i].edges.begin();
             edge != this->vertices[i].edges.end(); edge++) {
            edge->update_weight(edge->get_weight() + vertex_weights[i]
                - vertex_weights[edge->get_dest()]);
        }
    }

    vector<vector<int>> all_pairs_shortest_path_distances(this->num_vertices);

    // Get all pairs shortest path distances.
    for (int i = 0; i < this->num_vertices; i++)
        all_pairs_shortest_path_distances[i] = this->dijkstras_algorithm(i);

    // Update these distances to reflect the actual distances, not the
    // reweighted ones.
    for (int i = 0; i < all_pairs_shortest_path_distances.size(); i++)
        for (int j = 0; j < all_pairs_shortest_path_distances[i].size(); j++)
            all_pairs_shortest_path_distances[i][j]
                -= (vertex_weights[i] - vertex_weights[j]);

    // Revert graph to the original state.
    for (int i = 0; i < this->num_vertices; i++) {
        for (list<Edge>::iterator edge = this->vertices[i].edges.begin();
             edge != this->vertices[i].edges.end(); edge++) {
            edge->update_weight(edge->get_weight()
                - (vertex_weights[i] - vertex_weights[edge->get_dest()]));
        }
    }

    return all_pairs_shortest_path_distances;
}

vector<int> Graph::get_vertex_weights(void)
{
    // Create a new graph G' that is the reverse of the orignal graph, with
    // each vertex connected to a dummy vertex with edge length 0.
    Graph g_prime(this->num_vertices + 1);
    for (int i = 0; i < this->num_vertices; i++) {
        for (Edge edge : this->vertices[i].edges)
            g_prime.vertices[edge.get_dest()].add_edge(i, edge.get_weight());

        g_prime.vertices[i].add_edge(this->num_vertices, 0);
    }

    // Run Bellman-Ford on G' with source vertex as the newly added dummy
    // vertex.
    return g_prime.bellman_ford_algorithm(this->num_vertices);
}

vector<int> Graph::bellman_ford_algorithm(int src)
{
    const int MAX_INT = INT_MAX / 3;

    // Create a lookup table.
    vector<vector<int>> lookup_table(2);
    for (int i = 0; i < 2; i++)
        lookup_table[i].resize(this->num_vertices, MAX_INT);
    lookup_table[0][src] = 0;

    // Fill the lookup table.
    bool all_equal = true;
    for (int i = 0, x = 0; i < this->num_vertices; i++, x = (x + 1) % 2) {
        all_equal = true;
        for (int v = 0; v < this->num_vertices; v++) {
            int min_value = lookup_table[x][v];

            for (Edge edge : this->vertices[v].edges) {
                int curr_value
                    = lookup_table[x][edge.get_dest()] + edge.get_weight();
                if (curr_value < min_value) {
                    all_equal = false;
                    min_value = curr_value;
                }
            }

            lookup_table[(x + 1) % 2][v] = min_value;
        }

        // If there was no change in any value, that means the optimal path has
        // already been found.
        if (all_equal)
            break;
    }

    // If after n iterations, path still keeps getting more optimal, then cycle
    // exists.
    if (!all_equal)
        throw CycleExistsException();

    return lookup_table[0];
}

vector<int> Graph::dijkstras_algorithm(int src)
{
    const int MAX_INT = INT_MAX / 3;

    // Mark all vertices as unvisited.
    vector<bool> is_visited(this->num_vertices, false);

    // Initialize all distances.
    vector<int> distances(this->num_vertices, MAX_INT);
    distances[src] = 0;

    // Custom lambda function for comparisons.
    auto comparator
        = [](HeapNode &a, HeapNode &b) { return a.distance > b.distance; };

    // Create a Min Heap to store vertices sorted by their distance to the set
    // of vertices that has been processed.
    priority_queue<HeapNode, vector<HeapNode>, decltype(comparator)> heap(
        comparator);

    // Add all vertices to the heap, along with their distances from the
    // source.
    for (int i = 0; i < this->num_vertices; i++)
        heap.push(HeapNode(i, distances[i]));

    // Maintain count of processed vertices.
    int count = 0;
    while (count != this->num_vertices) {
        // Extract the node with minimum distance from the set of processed
        // vertices.
        HeapNode node = heap.top();
        heap.pop();

        if (!is_visited[node.vertex]) {
            is_visited[node.vertex] = true;

            // Update distances of the vertices that the popped vertex is
            // connected to.
            for (Edge edge : this->vertices[node.vertex].edges) {
                if (!is_visited[edge.get_dest()]) {
                    int distance = node.distance + edge.get_weight();

                    if (distance < distances[edge.get_dest()]) {
                        heap.push(HeapNode(edge.get_dest(), distance));
                        distances[edge.get_dest()] = distance;
                    }
                }
            }

            count++;
        }
    }

    return distances;
}