import java.util.LinkedList;

class Vertex {
  LinkedList<Edge> edges;

  Vertex() {
    this.edges = new LinkedList<>();
  }

  void addEdge(int dest, int weight) {
    this.edges.add(new Edge(dest, weight));
  }
}
