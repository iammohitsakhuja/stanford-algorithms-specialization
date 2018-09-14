import java.util.ArrayList;
import java.util.Collections;

class Graph {
  private int numberOfVertices;
  ArrayList<Edge> edges;

  Graph(int n) {
    this.numberOfVertices = n;
    this.edges = new ArrayList<Edge>();
  }

  void addEdge(int fromVertex, int toVertex, int length) {
    // Adjust for indexing.
    fromVertex--;
    toVertex--;

    this.edges.add(new Edge(fromVertex, toVertex, length));
  }

  int size() {
    return this.edges.size();
  }

  /** Finds the maximum spacing with k-clusters. */
  int findMaximumSpacing(int k) {
    // Sort the list of edges in ascending order of their lengths.
    Collections.sort(this.edges);

    // Initialize a UnionFind structure to keep track of different clusters.
    UnionFind uf = new UnionFind(this.numberOfVertices);

    // Get to the point where there are k clusters.
    int i = 0;
    for (int currentClusters = this.numberOfVertices;
        currentClusters > k && i < this.edges.size();
        i++) {
      Edge currEdge = this.edges.get(i);

      if (uf.find(currEdge.getFromVertex()) != uf.find(currEdge.getToVertex())) {
        uf.union(currEdge.getFromVertex(), currEdge.getToVertex());
        currentClusters--;
      }
    }

    // After k clusters have been formed, find the shortest edge with its end points in different
    // clusters.
    while (i < this.edges.size()
        && uf.find(this.edges.get(i).getFromVertex()) == uf.find(this.edges.get(i).getToVertex()))
      i++;

    // Max spacing will be 0 if there are 0 or 1 clusters.
    int maximumSpacing = i != this.edges.size() ? this.edges.get(i).getLength() : 0;

    return maximumSpacing;
  }
}
