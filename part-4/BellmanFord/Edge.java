class Edge {
  private int dest;
  private int weight;

  Edge() {
    this(0, 0);
  }

  Edge(int dest, int weight) {
    this.dest = dest;
    this.weight = weight;
  }

  int getDest() {
    return this.dest;
  }

  int getWeight() {
    return this.weight;
  }
}
