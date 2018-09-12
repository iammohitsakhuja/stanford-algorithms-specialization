import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

class PrimsMSTAlgorithm {
  static Graph loadGraph(String fileName) {
    Scanner reader = null;

    // Open file for reading.
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException e) {
      System.err.println("Error: File not found");
      e.printStackTrace();
      return null;
    }

    // Get the number of vertices, and number of edges.
    int numVertices = reader.hasNextInt() ? reader.nextInt() : 0;
    int numEdges = reader.hasNextInt() ? reader.nextInt() : 0;

    // Create a graph of appropriate size.
    Graph G = new Graph(numVertices);

    // Add the given edges in the graph.
    for (int i = 0; i < numEdges && reader.hasNextInt(); i++) {
      int tail = reader.nextInt();
      int head = reader.hasNextInt() ? reader.nextInt() : 0;
      int weight = reader.hasNextInt() ? reader.nextInt() : 0;

      G.addEdge(tail, head, weight);
    }

    // Housekeeping.
    reader.close();

    return G;
  }

  static int getOverallCost(ArrayList<HeapNode> minimumSpanningTree) {
    int sum = 0;
    for (int i = 0; i < minimumSpanningTree.size(); i++)
      sum += minimumSpanningTree.get(i).getWeight();

    return sum;
  }

  public static void main(String[] args) {
    if (args.length != 1) {
      System.err.println("Usage: java PrimsMSTAlgorithm <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Load the graph from the file.
    Graph G = loadGraph(fileName);
    if (G == null) {
      System.err.println("Graph could not be loaded");
      System.exit(2);
    }

    // Get the minimum spanning tree.
    ArrayList<HeapNode> minimumSpanningTree = G.getMinimumSpanningTree();

    System.out.println("Overall cost: " + getOverallCost(minimumSpanningTree));
  }
}
