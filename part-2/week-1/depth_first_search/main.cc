#include <iostream>

#include "Graph.hh"

using namespace std;

void test_graph1(void);
void test_graph2(void);

int main(void)
{
    test_graph1();
    test_graph2();
    printf("All tests passed!\n");
    return 0;
}

void test_graph1(void)
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
    list<int> traversed_vertices = G.dfs(1);
    assert(traversed_vertices.front() == 1);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 3);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 5);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 8);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 9);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());

    // Testing with vertex 5.
    traversed_vertices = G.dfs(5);
    assert(traversed_vertices.front() == 5);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 1);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 3);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 8);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 9);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("First cluster found!\n");

    // Testing with vertex 2.
    traversed_vertices = G.dfs(2);
    assert(traversed_vertices.front() == 2);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 6);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("Second cluster found!\n");

    // Testing with vertex 4.
    traversed_vertices = G.dfs(4);
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());

    // Testing with vertex 7.
    traversed_vertices = G.dfs(7);
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("Third cluster found!\n");
    printf("First set of tests passed!\n\n");
}

void test_graph2(void)
{
    // Setup.
    const int n = 7;
    Graph G(n);
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(2, 4);
    G.add_edge(3, 4);
    G.add_edge(3, 5);
    G.add_edge(4, 6);
    G.add_edge(5, 6);
    G.add_edge(5, 7);
    G.add_edge(6, 7);

    // Testing.
    list<int> traversed_vertices = G.dfs(1);
    assert(traversed_vertices.front() == 1);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 2);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 6);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 5);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 3);
    traversed_vertices.pop_front();

    assert(traversed_vertices.empty());
    printf("Full graph traversed!\n");
    printf("Second set of tests passed!\n\n");
}
