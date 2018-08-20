#include <iostream>

#include "Graph.hh"

using namespace std;

void test(void);

int main(void)
{
    test();
    printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    // Setup.
    const int n = 10;
    Graph G(n);
    // First cluster.
    G.add_edge(1, 3);
    G.add_edge(1, 5);
    G.add_edge(3, 5);
    G.add_edge(5, 8);
    G.add_edge(5, 9);

    // Second cluster.
    G.add_edge(2, 6);

    // Third cluster.
    G.add_edge(4, 7);
    G.add_edge(4, 10);

    // Testing with vertex 1.
    list<int> traversed_vertices = G.bfs(1);
    assert(traversed_vertices.front() == 1);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 5);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 3);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 9);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 8);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());

    // Testing with vertex 5.
    traversed_vertices = G.bfs(5);
    assert(traversed_vertices.front() == 5);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 9);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 8);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 3);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 1);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("First cluster found!\n");

    // Testing with vertex 2.
    traversed_vertices = G.bfs(2);
    assert(traversed_vertices.front() == 2);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 6);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("Second cluster found!\n");

    // Testing with vertex 4.
    traversed_vertices = G.bfs(4);
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());

    // Testing with vertex 7.
    traversed_vertices = G.bfs(7);
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("Third cluster found!\n");
}
