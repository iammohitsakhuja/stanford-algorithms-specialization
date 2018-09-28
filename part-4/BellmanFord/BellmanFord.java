import java.util.ArrayList;
import java.util.LinkedList;

class BellmanFord {
  static void testWithoutNegativeCostCycle() {
    // Setup.
    Graph graph = new Graph(5);

    graph.addEdge(1, 2, -1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 2);
    graph.addEdge(2, 5, 2);
    graph.addEdge(4, 2, 1);
    graph.addEdge(4, 3, 5);
    graph.addEdge(5, 4, -3);

    // Assert that `getShortestPaths` does not return `null` as there is no negative cost cycle.
    ArrayList<LinkedList<Edge>> paths = graph.getShortestPathsFrom(1);
    assert paths != null;
    assert paths.size() == 5;

    // Test.
    assert paths.get(0).size() == 0;

    LinkedList<Edge> list = paths.get(1);
    assert list.size() == 1;
    assert list.get(0).getDest() + 1 == 2 && list.get(0).getWeight() == -1;

    list = paths.get(2);
    assert list.size() == 2;
    assert list.get(0).getDest() + 1 == 2 && list.get(0).getWeight() == -1;
    assert list.get(1).getDest() + 1 == 3 && list.get(1).getWeight() == 3;

    list = paths.get(3);
    assert list.size() == 3;
    assert list.get(0).getDest() + 1 == 2 && list.get(0).getWeight() == -1;
    assert list.get(1).getDest() + 1 == 5 && list.get(1).getWeight() == 2;
    assert list.get(2).getDest() + 1 == 4 && list.get(2).getWeight() == -3;

    list = paths.get(4);
    assert list.size() == 2;
    assert list.get(0).getDest() + 1 == 2 && list.get(0).getWeight() == -1;
    assert list.get(1).getDest() + 1 == 5 && list.get(1).getWeight() == 2;

    System.out.println("Test without negative cost cycle passed successfully!");
  }

  static void testWithNegativeCostCycle() {
    // Setup.
    Graph graph = new Graph(8);

    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 4);
    graph.addEdge(3, 5, 4);
    graph.addEdge(3, 6, -2);
    graph.addEdge(4, 1, 3);
    graph.addEdge(4, 3, 2);
    graph.addEdge(5, 4, 1);
    graph.addEdge(5, 7, -2);
    graph.addEdge(6, 2, 3);
    graph.addEdge(6, 5, -3);
    graph.addEdge(7, 6, 2);
    graph.addEdge(7, 8, 2);
    graph.addEdge(8, 5, -2);

    // Assert that `getShortestPaths` returns `null` as there exists a negative cost cycle.
    ArrayList<LinkedList<Edge>> paths = graph.getShortestPathsFrom(1);
    assert paths == null;

    // Get the vertices in the cycle.
    LinkedList<Integer> cycle = graph.getCycle();

    // Test.
    int[] expectedCycle = new int[] {7, 6, 5};
    for (int i = 0; i < expectedCycle.length && !cycle.isEmpty(); i++) {
      int vertex = cycle.pollFirst();
      assert vertex == expectedCycle[i];
    }

    System.out.println("Test with negative cost cycle(s) passed successfully!");
  }

  public static void main(String[] args) {
    testWithoutNegativeCostCycle();
    testWithNegativeCostCycle();
    System.out.println("All tests complete!");
  }
}
