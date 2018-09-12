class Edge {
  private int head; /* The vertex that the head is pointing towards. */
  private int weight; /* The weight of the edge. */

  Edge(int head, int weight) {
    this.head = head;
    this.weight = weight;
  }

  int getHead() {
    return this.head;
  }

  int getWeight() {
    return this.weight;
  }
}
