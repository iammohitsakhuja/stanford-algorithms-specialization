class MSTNode {
  private int fromVertex;
  private int toVertex;
  private int length;

  MSTNode(int fromVertex, int toVertex, int length) {
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

  void setFromVertex(int fromVertex) {
    this.fromVertex = fromVertex;
  }

  void setToVertex(int toVertex) {
    this.toVertex = toVertex;
  }
}
