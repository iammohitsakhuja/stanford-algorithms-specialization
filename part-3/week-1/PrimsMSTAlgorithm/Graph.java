import java.util.ArrayList;

class Graph {
  private int n;
  private Vertex[] vertices;

  Graph(int n) {
    this.n = n;
    this.vertices = new Vertex[n];
    for (int i = 0; i < n; i++) this.vertices[i] = new Vertex();
  }

  void addEdge(int tail, int head, int weight) {
    // Adjust for indexing.
    tail--;
    head--;

    // Add undirected edge between the vertices.
    this.vertices[tail].addEdge(head, weight);
    this.vertices[head].addEdge(tail, weight);
  }

  ArrayList<HeapNode> getMinimumSpanningTree() {
    // Create an arraylist to hold the MST.
    ArrayList<HeapNode> minimumSpanningTree = new ArrayList<HeapNode>();

    // Create an array to know which vertices have been processed/added to the tree.
    boolean[] isProcessed = new boolean[this.n];

    // Create a heap.
    Heap unprocessedNodes = new Heap(this.n);

    // Add all vertices to the heap.
    unprocessedNodes.push(new HeapNode(0, 0, 0));
    for (int i = 1; i < this.n; i++) unprocessedNodes.push(new HeapNode(0, i, Integer.MAX_VALUE));

    while (!unprocessedNodes.isEmpty()) {
      // Get the vertex closest to the current tree.
      HeapNode currentVertex = unprocessedNodes.top();
      unprocessedNodes.pop();

      // Set this vertex as processed.
      isProcessed[currentVertex.getHead()] = true;

      // For each of the unprocessed vertices (w) that this vertex (v) is connected to, recalculate
      // their distance.
      for (Edge edge : this.vertices[currentVertex.getHead()].edges) {
        if (!isProcessed[edge.getHead()]) {
          // Get the weight of this vertex (w) that is currently in the heap.
          HeapNode heapNode = unprocessedNodes.getElementWithKey(edge.getHead());

          // If the weight of the vertex `w` in the heap is more than the weight of the same vertex
          // from `v`.
          if (edge.getWeight() < heapNode.getWeight()) {
            // Delete vertex `w` from the the heap.
            unprocessedNodes.deleteElementWithKey(edge.getHead());

            // Update its tail vertex and new weight.
            heapNode.setTail(currentVertex.getHead());
            heapNode.setWeight(edge.getWeight());

            // Add the vertex back to the heap.
            unprocessedNodes.push(heapNode);
          }
        }
      }

      // Update the current vertex `v` to adjust for indexing, then add it to the tree.
      currentVertex.setTail(currentVertex.getTail() + 1);
      currentVertex.setHead(currentVertex.getHead() + 1);
      minimumSpanningTree.add(currentVertex);
    }

    return minimumSpanningTree;
  }

  /** Helper function for debugging. */
  void print() {
    for (int i = 0; i < n; i++) {
      System.out.print((i + 1) + " -> ");
      for (Edge e : this.vertices[i].edges)
        System.out.print((e.getHead() + 1) + "," + e.getWeight() + " ");
      System.out.println();
    }
  }
}
