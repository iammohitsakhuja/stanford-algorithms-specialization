class Edge implements Comparable<Edge> {
  private int fromVertex;
  private int toVertex;
  private int length;

  Edge(int fromVertex, int toVertex, int length) {
    this.fromVertex = fromVertex;
    this.toVertex = toVertex;
    this.length = length;
  }

  int getFromVertex() {
    return this.fromVertex;
  }

  int getToVertex() {
    return this.toVertex;
  }

  int getLength() {
    return this.length;
  }

  @Override
  public int compareTo(Edge e) {
    return this.length - e.length;
  }
}
