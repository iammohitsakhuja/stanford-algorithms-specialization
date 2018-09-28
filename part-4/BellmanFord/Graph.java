import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Stack;

class Graph {
  int numVertices;
  Vertex[] vertices;
  private boolean cycleExists;
  private LookupTableEntry[][] lookupTable;

  Graph(int numVertices) {
    this.numVertices = numVertices;
    this.vertices = new Vertex[this.numVertices];

    // Initialize each vertex of the graph.
    for (int i = 0; i < this.numVertices; i++) this.vertices[i] = new Vertex();

    this.cycleExists = false;
    this.lookupTable = null;
  }

  void addEdge(int src, int dest, int weight) {
    // Adjust for indexing.
    src--;
    dest--;

    this.vertices[src].addEdge(dest, weight);
  }

  void print() {
    for (int i = 0; i < this.numVertices; i++) {
      System.out.print(i + 1 + " -> ");
      for (Edge edge : this.vertices[i].edges)
        System.out.print("(" + (edge.getDest() + 1) + ", " + edge.getWeight() + ") ");
      System.out.println();
    }
  }

  Graph createReversedGraph() {
    Graph reverseGraph = new Graph(this.numVertices);

    for (int i = 0; i < this.numVertices; i++)
      for (Edge edge : this.vertices[i].edges)
        reverseGraph.addEdge(edge.getDest() + 1, i + 1, edge.getWeight());

    return reverseGraph;
  }

  static class LookupTableEntry {
    long value;
    int lastHopVertex;

    LookupTableEntry(long value, int lastHopVertex) {
      this.value = value;
      this.lastHopVertex = lastHopVertex;
    }

    @Override
    public String toString() {
      return "[" + this.value + ", " + (this.lastHopVertex + 1) + "]";
    }
  }

  /** Reconstruct shortest paths from source using a lookup table. */
  private ArrayList<LinkedList<Edge>> reconstructShortestPaths(
      LookupTableEntry[][] lookupTable, int src) {
    // Indicates whether the path to a vertex has already been calculated.
    boolean[] addedToPath = new boolean[this.numVertices];

    // Path to each vertex is a linked list of edges.
    ArrayList<LinkedList<Edge>> shortestPaths = new ArrayList<>(this.numVertices);
    for (int i = 0; i < this.numVertices; i++) shortestPaths.add(null);

    // Path to source need not be calculated.
    addedToPath[src] = true;
    shortestPaths.set(src, new LinkedList<Edge>());

    for (int i = 0; i < this.numVertices; i++) {
      if (addedToPath[i]) continue;

      // For containing unprocessed vertices that are in the current path.
      Stack<Edge> verticesInCurrentPath = new Stack<>();

      int currVertex = i;
      while (!addedToPath[currVertex]) {
        int lastHopVertex = lookupTable[0][currVertex].lastHopVertex;
        int currEdgeWeight =
            (int) lookupTable[0][currVertex].value - (int) lookupTable[0][lastHopVertex].value;

        // Push the current vertex along with the distance of this vertex from the last hop vertex
        // into the stack.
        verticesInCurrentPath.push(new Edge(currVertex, currEdgeWeight));

        addedToPath[currVertex] = true;
        currVertex = lastHopVertex;
      }

      while (!verticesInCurrentPath.isEmpty()) {
        // Get the topmost vertex in the stack.
        Edge currEdge = verticesInCurrentPath.peek();
        verticesInCurrentPath.pop();

        // The path to this vertex is equal to the path to its previous vertex with the last hop
        // edge concatenated to it.
        shortestPaths.set(currEdge.getDest(), new LinkedList<Edge>(shortestPaths.get(currVertex)));
        shortestPaths.get(currEdge.getDest()).add(currEdge);

        currVertex = currEdge.getDest();
      }
    }

    return shortestPaths;
  }

  /**
   * Returns the elements in a cycle in the graph, if it exists. Must call `getShortestPaths` first.
   */
  LinkedList<Integer> getCycle() {
    if (!this.cycleExists || this.lookupTable == null) return null;

    // Find the vertex whose path optimality has improved.
    int row = this.numVertices % 2;
    int vertex = -1;
    for (int i = 0, x = (row + 1) % 2; i < this.lookupTable[row].length; i++)
      if (this.lookupTable[row][i].value < this.lookupTable[x][i].value) {
        vertex = i;
        break;
      }

    // List to store elements in the cycle.
    LinkedList<Integer> cycle = new LinkedList<>();

    // Keep track of the vertices that have been traversed already.
    boolean[] traversedAlready = new boolean[this.numVertices];

    // Get to the vertex that is the entry point of the cycle.
    while (!traversedAlready[vertex]) {
      traversedAlready[vertex] = true;
      vertex = this.lookupTable[row][vertex].lastHopVertex;
    }

    // Add the elements in the cycle to the list in the order in which they form a cycle.
    do {
      cycle.addFirst(vertex + 1);
      vertex = this.lookupTable[row][vertex].lastHopVertex;
    } while (vertex + 1 != cycle.peekLast());

    return cycle;
  }

  ArrayList<LinkedList<Edge>> getShortestPathsFrom(int src) {
    // Make sure to clean the results of any previous operations.
    this.cycleExists = false;
    this.lookupTable = null;

    // Create a graph that represents edges going into a vertex, instead of out.
    Graph reverseGraph = this.createReversedGraph();

    // Adjust for indexing.
    src--;

    // Create a lookup table.
    LookupTableEntry[][] lookupTable = new LookupTableEntry[2][this.numVertices];
    for (int i = 0; i < 2; i++)
      for (int v = 0; v < this.numVertices; v++)
        lookupTable[i][v] = new LookupTableEntry(Integer.MAX_VALUE, -1);
    lookupTable[0][src].value = 0;

    // Fill the lookup table.
    boolean allEqual = true;
    for (int i = 0, x = 0; i < this.numVertices; i++, x = (x + 1) % 2) {
      allEqual = true;
      for (int v = 0; v < this.numVertices; v++) {
        LookupTableEntry minValueEntry = lookupTable[x][v];

        for (Edge edge : reverseGraph.vertices[v].edges) {
          long currValue = lookupTable[x][edge.getDest()].value + edge.getWeight();
          if (currValue < minValueEntry.value) {
            allEqual = false;
            minValueEntry = new LookupTableEntry(currValue, edge.getDest());
          }
        }

        lookupTable[(x + 1) % 2][v] = minValueEntry;
      }

      // If there was no change in any value, that means the optimal path has already been found.
      if (allEqual) break;
    }

    // If after n iterations, path still gets more optimal, then cycle exists.
    if (!allEqual) {
      this.cycleExists = true;
      this.lookupTable = lookupTable;

      return null;
    }

    // Reconstruct the path.
    return this.reconstructShortestPaths(lookupTable, src);
  }
}
