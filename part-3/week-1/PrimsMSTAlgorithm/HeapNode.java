class HeapNode {
  private int tail;
  private int head;
  private int weight;

  HeapNode(int tail, int head, int weight) {
    this.tail = tail;
    this.head = head;
    this.weight = weight;
  }

  int getTail() {
    return this.tail;
  }

  int getHead() {
    return this.head;
  }

  int getWeight() {
    return this.weight;
  }

  void setTail(int tail) {
    this.tail = tail;
  }

  void setHead(int head) {
    this.head = head;
  }

  void setWeight(int weight) {
    this.weight = weight;
  }
}
