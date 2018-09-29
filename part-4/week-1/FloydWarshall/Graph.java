class Graph {
  private Vertex[] vertices;
  private int numVertices;

  Graph(int numVertices) {
    this.numVertices = numVertices;
    this.vertices = new Vertex[this.numVertices];
    for (int i = 0; i < this.numVertices; i++) this.vertices[i] = new Vertex();
  }

  /** Add directed edge to a graph. */
  void addEdge(int src, int dest, int weight) {
    // Adjust for indexing.
    src--;
    dest--;

    // Add directed edge.
    this.vertices[src].addEdge(dest, weight);
  }

  /** Get all pairs shortest paths for a directed weighted graph. */
  long[][] getAllPairsShortestPaths() {
    // Lookup table for caching previously computed results.
    long[][][] lookupTable = new long[2][this.numVertices][this.numVertices];

    // Initialize lookup table with appropriate values when i != j.
    for (int i = 0; i < this.numVertices; i++)
      for (int j = 0; j < this.numVertices; j++)
        if (i != j) lookupTable[0][i][j] = Integer.MAX_VALUE;

    // Initialize lookup table with appropriate values when there exists a directed edge from i to
    // j.
    for (int i = 0; i < this.numVertices; i++)
      for (Edge edge : this.vertices[i].edges) lookupTable[0][i][edge.getDest()] = edge.getWeight();

    // Fill the rest of the lookup table.
    for (int k = 1, x = 0, y = 1; k < this.numVertices; k++, x = (x + 1) % 2, y = (y + 1) % 2)
      for (int i = 0; i < this.numVertices; i++)
        for (int j = 0; j < this.numVertices; j++)
          lookupTable[y][i][j] =
              Long.min(lookupTable[x][i][j], lookupTable[x][i][k] + lookupTable[x][k][j]);

    // Check for negative edge cost cycle by going through the diagonal.
    for (int i = 0, plane = (this.numVertices + 1) % 2; i < this.numVertices; i++)
      if (lookupTable[plane][i][i] < 0) return null;

    return lookupTable[(this.numVertices + 1) % 2];
  }

  /** Helper function for printing the graph. */
  void print() {
    for (int i = 0; i < this.numVertices; i++)
      for (Edge edge : this.vertices[i].edges)
        System.out.println(
            (i + 1) + " -> (" + (edge.getDest() + 1) + ", " + edge.getWeight() + ")");
  }
}
