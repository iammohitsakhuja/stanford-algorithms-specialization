#include <iostream>

#include "Graph.hh"

using namespace std;

int main(void)
{
    int n;
    printf("Enter number of vertices: ");
    scanf("%i", &n);

    Graph G(n);

    int m;
    printf("Enter number of edges: ");
    scanf("%i", &m);
    for (int i = 0; i < m; i++) {
        int v, w;
        printf("Enter v, w: ");
        scanf("%i %i", &v, &w);

        if (!(v >= 0 && v < n && w >= 0 && w < n)) {
            fprintf(stderr, "v, w must be in [0, n)\n");
            return 1;
        }

        G.add_edge(v, w);
    }

    int s;
    printf("Enter the edge number from where to start the BFS, s: ");
    scanf("%i", &s);

    if (s < 0 || s >= n) {
        fprintf(stderr, "s must be in [0, n)\n");
        return 2;
    }

    G.bfs(s);

    return 0;
}