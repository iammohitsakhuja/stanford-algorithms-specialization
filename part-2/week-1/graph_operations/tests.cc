#include "tests.hh"

#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;

static void test_graph1(void);
static void test_graph2(void);

void test_bfs(void)
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
    list<int> traversed_vertices = G.bfs(1, true);
    int expected_output1[]       = { 1, 5, 3, 9, 8 };
    for (int i = 0; i < 5; i++) {
        assert(traversed_vertices.front() == expected_output1[i]);
        traversed_vertices.pop_front();
    }
    assert(traversed_vertices.empty());

    // Testing with vertex 5.
    traversed_vertices     = G.bfs(5, true);
    int expected_output2[] = { 5, 9, 8, 3, 1 };
    for (int i = 0; i < 5; i++) {
        assert(traversed_vertices.front() == expected_output2[i]);
        traversed_vertices.pop_front();
    }
    assert(traversed_vertices.empty());

    // Testing with vertex 2.
    traversed_vertices = G.bfs(2, true);
    assert(traversed_vertices.front() == 2);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 6);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());

    // Testing with vertex 4.
    traversed_vertices = G.bfs(4, true);
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());

    // Testing with vertex 7.
    traversed_vertices = G.bfs(7, true);
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());

    printf("BFS tests passed!\n");
}

void test_get_shortest_path(void)
{
    // Setup.
    const int n = 12;
    Graph G(n);

    // First cluster.
    G.add_edge(1, 2);
    G.add_edge(1, 6);
    G.add_edge(2, 4);
    G.add_edge(4, 6);
    G.add_edge(4, 7);
    G.add_edge(4, 9);
    G.add_edge(6, 7);
    G.add_edge(7, 9);

    // Second cluster.
    G.add_edge(3, 5);
    G.add_edge(3, 8);
    G.add_edge(5, 8);
    G.add_edge(8, 10);

    // Third cluster contains a self loop. Fourth contains no edges.
    G.add_edge(11, 11);

    // Testing.
    assert(G.get_shortest_path(1, 1) == 0);
    assert(G.get_shortest_path(1, 9) == 3);
    assert(G.get_shortest_path(1, 3) == -1);
    assert(G.get_shortest_path(1, 7) == 2);
    assert(G.get_shortest_path(3, 10) == 2);
    assert(G.get_shortest_path(8, 10) == 1);
    assert(G.get_shortest_path(3, 4) == -1);
    assert(G.get_shortest_path(5, 5) == 0);
    assert(G.get_shortest_path(11, 1) == -1);
    assert(G.get_shortest_path(11, 3) == -1);
    assert(G.get_shortest_path(11, 11) == 0);
    assert(G.get_shortest_path(12, 12) == 0);

    printf("Shortest path tests passed!\n");
}

void test_find_connected_components(void)
{
    // Setup.
    const int n = 10;
    Graph G(n);

    // First cluster.
    G.add_edge(1, 3);
    G.add_edge(1, 5);
    G.add_edge(3, 5);
    G.add_edge(5, 7);
    G.add_edge(5, 9);

    // Second cluster.
    G.add_edge(2, 4);

    // Third cluster.
    G.add_edge(6, 8);
    G.add_edge(6, 10);
    G.add_edge(8, 10);

    // Testing.
    list<list<int>> connected_components = G.find_connected_components();
    assert(connected_components.size() == 3);

    // Testing the values of each of those components.
    const int expected_components[3][5]
        = { { 1, 5, 3, 9, 7 }, { 2, 4 }, { 6, 10, 8 } };
    for (int i = 0, size = connected_components.size(); i < size; i++) {
        int j = 0;
        while (!connected_components.front().empty()) {
            assert(connected_components.front().front()
                == expected_components[i][j++]);
            connected_components.front().pop_front();
        }
        assert(connected_components.front().empty());
        connected_components.pop_front();
    }
    printf("Connected components tests passed!\n");
}

void test_dfs(void)
{
    test_graph1();
    test_graph2();
    printf("DFS tests passed!\n");
}

void test_topological_sort(void)
{
    // Setup.
    const int n = 6;
    Graph G(n);
    G.add_edge(3, 4, true);
    G.add_edge(4, 2, true);
    G.add_edge(5, 1, true);
    G.add_edge(5, 2, true);
    G.add_edge(6, 1, true);
    G.add_edge(6, 3, true);

    // Test.
    list<int> sorted_vertices    = G.topological_sort();
    const int expected_output[n] = { 6, 5, 3, 4, 2, 1 };
    for (int i = 0; i < n; i++) {
        assert(sorted_vertices.front() == expected_output[i]);
        sorted_vertices.pop_front();
    }
    assert(sorted_vertices.empty());
    printf("Topological sort tests passed!\n");
}

void test_reverse(Graph &G)
{
    Graph rev = G.create_reverse_graph();
    assert(rev.is_reverse_of(G));
    printf("Reversing tests passed!\n");
}

// Function used by dfs testing function.
static void test_graph1(void)
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
    list<int> traversed_vertices = G.dfs(1, true);
    int expected_output1[]       = { 1, 3, 5, 8, 9 };
    for (int i = 0; i < 5; i++) {
        assert(traversed_vertices.front() == expected_output1[i]);
        traversed_vertices.pop_front();
    }
    assert(traversed_vertices.empty());

    // Testing with vertex 5.
    traversed_vertices     = G.dfs(5, true);
    int expected_output2[] = { 5, 1, 3, 8, 9 };
    for (int i = 0; i < 5; i++) {
        assert(traversed_vertices.front() == expected_output2[i]);
        traversed_vertices.pop_front();
    }
    assert(traversed_vertices.empty());

    // Testing with vertex 2.
    traversed_vertices = G.dfs(2, true);
    assert(traversed_vertices.front() == 2);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 6);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());

    // Testing with vertex 4.
    traversed_vertices = G.dfs(4, true);
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());

    // Testing with vertex 7.
    traversed_vertices = G.dfs(7, true);
    assert(traversed_vertices.front() == 7);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 4);
    traversed_vertices.pop_front();
    assert(traversed_vertices.front() == 10);
    traversed_vertices.pop_front();
    assert(traversed_vertices.empty());
}

// Function used by dfs testing function.
static void test_graph2(void)
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
    list<int> traversed_vertices = G.dfs(1, true);
    int expected_output[]        = { 1, 2, 4, 6, 5, 7, 3 };
    for (int i = 0; i < 7; i++) {
        assert(traversed_vertices.front() == expected_output[i]);
        traversed_vertices.pop_front();
    }
    assert(traversed_vertices.empty());
}
