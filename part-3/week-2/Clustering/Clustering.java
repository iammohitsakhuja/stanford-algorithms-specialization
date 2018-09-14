import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Clustering {
  /** Loads the graph from a file. */
  static Graph loadGraphFromFile(String fileName) {
    Scanner reader = null;

    // Open file for reading.
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException e) {
      System.err.println("Error: File not found");
      e.printStackTrace();
      return null;
    }

    // Read the size of the graph from the file.
    int numberOfVertices = reader.hasNextInt() ? reader.nextInt() : 0;

    // Create a graph of appropriate size.
    Graph graph = new Graph(numberOfVertices);

    // Read the edges from the file.
    while (reader.hasNextInt()) {
      int fromVertex = reader.nextInt();
      int toVertex = reader.hasNextInt() ? reader.nextInt() : 0;
      int length = reader.hasNextInt() ? reader.nextInt() : 0;

      graph.addEdge(fromVertex, toVertex, length);
    }

    // Housekeeping.
    reader.close();

    return graph;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 2) {
      System.err.println("Usage: java Clustering <fileName> <numClusters>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];
    int numberOfClusters = 0;

    try {
      numberOfClusters = Integer.parseInt(args[1]);
    } catch (NumberFormatException e) {
      System.err.println("numClusters must be an integer");
      System.exit(2);
    }

    // Benchmarks.
    double timeLoadingGraph = 0.0;
    double timeFindingMaxSpacing = 0.0;

    // Load the graph from the file and benchmark the time taken.
    long startTime = System.nanoTime();
    Graph graph = loadGraphFromFile(fileName);
    timeLoadingGraph = (System.nanoTime() - startTime) / 1000000.0;
    if (graph == null) {
      System.err.println("Graph could not be loaded");
      System.exit(3);
    }

    // Get the max spacing for the given number of clusters and benchmark the time taken to
    // calculate it.
    startTime = System.nanoTime();
    int maxSpacing = graph.findMaximumSpacing(numberOfClusters);
    timeFindingMaxSpacing = (System.nanoTime() - startTime) / 1000000.0;

    System.out.println("Maximum spacing: " + maxSpacing + "\n");

    // Display the benchmark results.
    System.out.printf("TIME IN loading graph:           %6.2fms\n", timeLoadingGraph);
    System.out.printf("TIME IN finding the max spacing: %6.2fms\n", timeFindingMaxSpacing);
  }
}
