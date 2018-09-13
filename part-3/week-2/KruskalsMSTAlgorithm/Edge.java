class Edge {
  private int toVertex;
  private int length;

  Edge(int toVertex, int length) {
    this.toVertex = toVertex;
    this.length = length;
  }

  int getToVertex() {
    return this.toVertex;
  }

  int getLength() {
    return this.length;
  }
}
