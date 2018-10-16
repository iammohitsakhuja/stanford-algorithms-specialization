#include <algorithm>
#include <stack>

#include "Graph.hh"

using namespace std;

Graph::Graph(int num_vertices)
    : num_vertices(num_vertices)
{
    this->vertices = new Vertex[num_vertices];
}

void Graph::add_edge(int src, int dest)
{
    this->vertices[src].edges.push_back(dest);
}

Graph *Graph::create_reverse_graph(void)
{
    Graph *rev_graph = new Graph(this->num_vertices);

    for (int i = 0; i < this->num_vertices; i++)
        for (int j = 0; j < this->vertices[i].edges.size(); j++)
            rev_graph->add_edge(this->vertices[i].edges[j], i);

    return rev_graph;
}

vector<int> Graph::get_topological_sorting(void)
{
    // Mark all vertices as unvisited.
    for (int i = 0; i < this->num_vertices; i++)
        this->vertices[i].is_visited = false;

    vector<int> topologically_sorted_vertices;
    topologically_sorted_vertices.reserve(this->num_vertices - 1);

    for (int i = this->num_vertices - 1; i > 0; i--)
        if (!this->vertices[i].is_visited)
            this->dfs(i, topologically_sorted_vertices);

    // Mark all vertices as unvisited again.
    for (int i = 0; i < this->num_vertices; i++)
        this->vertices[i].is_visited = false;

    return topologically_sorted_vertices;
}

void Graph::dfs(
    int src, vector<int> &topologically_sorted_vertices, bool set_unvisited)
{
    if (set_unvisited)
        for (int i = 0; i < this->num_vertices; i++)
            this->vertices[i].is_visited = false;

    // Create a stack to hold vertices. (Used to avoid recursion).
    stack<int> vertices_in_stack;

    // Mark the src vertex as visited and add it to the stack.
    this->vertices[src].is_visited = true;
    vertices_in_stack.push(src);

    while (!vertices_in_stack.empty()) {
        int top = vertices_in_stack.top();

        bool all_done = true;
        for (int &w : this->vertices[top].edges) {
            if (!this->vertices[w].is_visited) {
                all_done                     = false;
                this->vertices[w].is_visited = true;
                vertices_in_stack.push(w);
                break;
            }
        }

        if (all_done) {
            topologically_sorted_vertices.push_back(vertices_in_stack.top());
            vertices_in_stack.pop();
        }
    }

    // Mark vertices as unvisited again.
    if (set_unvisited)
        for (int i = 0; i < this->num_vertices; i++)
            this->vertices[i].is_visited = false;
}

vector<int> Graph::compute_sccs(void)
{
    // Create a reversed graph.
    Graph *rev_graph = this->create_reverse_graph();

    // Get the topological sorting of the vertices (ascending f-values) for the
    // reversed graph.
    vector<int> topologically_sorted_vertices
        = rev_graph->get_topological_sorting();

    // Finally, compute the SCCs.
    vector<int> strongly_connected_components(this->num_vertices);

    // Start from the vertex with the highest f-value in the reverse graph's
    // topological sorting, and run dfs on that vertex in the original graph,
    // if it is unvisited.
    for_each(topologically_sorted_vertices.rbegin(),
        topologically_sorted_vertices.rend(), [&](int &v) {
            if (!this->vertices[v].is_visited) {
                vector<int> temp;
                this->dfs(v, temp);

                for (int &w : temp)
                    strongly_connected_components[w] = v;
            }
        });

    return strongly_connected_components;
}

void Graph::print(void)
{
    for (int i = 0; i < this->num_vertices; i++) {
        printf("%i -> ", i);
        for (int j = 0; j < this->vertices[i].edges.size(); j++) {
            printf("%i ", this->vertices[i].edges[j]);
        }
        printf("\n");
    }
}
