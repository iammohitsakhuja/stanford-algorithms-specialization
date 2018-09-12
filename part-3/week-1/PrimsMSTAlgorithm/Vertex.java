import java.util.LinkedList;

class Vertex {
  LinkedList<Edge> edges;

  Vertex() {
    edges = new LinkedList<Edge>();
  }

  void addEdge(int head, int weight) {
    edges.push(new Edge(head, weight));
  }
}
