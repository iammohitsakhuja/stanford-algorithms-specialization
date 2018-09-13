import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

class Graph {
  private class SortByEdgeLengths implements Comparator<MSTNode> {
    public int compare(MSTNode a, MSTNode b) {
      return a.getLength() - b.getLength();
    }
  }

  // Members.
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

  private ArrayList<MSTNode> getSortedListOfEdges() {
    // Create a list that will contain all edges (this list will contain duplicate edges too but it
    // won't matter).
    ArrayList<MSTNode> edges = new ArrayList<MSTNode>();

    // Add each edge to this list.
    for (int i = 0; i < this.n; i++)
      for (Edge e : this.vertices[i].edges)
        edges.add(new MSTNode(i, e.getToVertex(), e.getLength()));

    // Sort the given list in the increasing order of edge lengths.
    Collections.sort(edges, new SortByEdgeLengths());

    return edges;
  }

  ArrayList<MSTNode> getMinimumSpanningTree() {
    // Create an list containing all edges and their vertices.
    ArrayList<MSTNode> edges = this.getSortedListOfEdges();

    // Initialize a UnionFind structure.
    UnionFind uf = new UnionFind(this.n);

    // A list to hold the final MST.
    ArrayList<MSTNode> minimumSpanningTree = new ArrayList<MSTNode>();

    // Iterate through each of the sorted edges.
    for (MSTNode edge : edges) {
      // If the two vertices of this edge are not in the same subset, then add this edge to the MST.
      if (uf.find(edge.getFromVertex()) != uf.find(edge.getToVertex())) {
        uf.union(edge.getFromVertex(), edge.getToVertex());

        // Re-adjust for indexing.
        edge.setFromVertex(edge.getFromVertex() + 1);
        edge.setToVertex(edge.getToVertex() + 1);

        minimumSpanningTree.add(edge);
      }
    }

    return minimumSpanningTree;
  }

  /** Helper function for debugging. */
  void print() {
    for (int i = 0; i < n; i++) {
      System.out.print((i + 1) + " -> ");
      for (Edge e : this.vertices[i].edges)
        System.out.print((e.getToVertex() + 1) + "," + e.getLength() + " ");
      System.out.println();
    }
  }
}
