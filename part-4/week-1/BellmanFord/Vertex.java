import java.util.LinkedList;
import java.util.List;

class Vertex {
  List<Edge> edges;

  Vertex() {
    this.edges = new LinkedList<>();
  }

  void addEdge(int dest, int weight) {
    this.edges.add(new Edge(dest, weight));
  }
}
