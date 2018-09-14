import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

class KruskalsMSTAlgorithm {
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

  static int getOverallCost(ArrayList<MSTNode> minimumSpanningTree) {
    int sum = 0;
    for (int i = 0; i < minimumSpanningTree.size(); i++)
      sum += minimumSpanningTree.get(i).getLength();

    return sum;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java KruskalsMSTAlgorithm <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Benchmarks.
    double timeLoadingGraph = 0.0;
    double timeFindingMST = 0.0;

    // Load the graph from the file and benchmark the time taken.
    long startTime = System.nanoTime();
    Graph G = loadGraph(fileName);
    timeLoadingGraph = (System.nanoTime() - startTime) / 1000000.0;
    if (G == null) {
      System.err.println("Graph could not be loaded");
      System.exit(2);
    }

    // Get the minimum spanning tree and benchmark the time taken.
    startTime = System.nanoTime();
    ArrayList<MSTNode> minimumSpanningTree = G.getMinimumSpanningTree();
    timeFindingMST = (System.nanoTime() - startTime) / 1000000.0;
    if (minimumSpanningTree == null) {
      System.err.println("No minimum spanning tree");
      System.exit(3);
    }

    System.out.println("Overall cost: " + getOverallCost(minimumSpanningTree) + "\n");

    // Display the benchmark results.
    System.out.printf("TIME IN loading graph:   %6.2fms\n", timeLoadingGraph);
    System.out.printf("TIME IN finding the MST: %6.2fms\n", timeFindingMST);
  }
}
