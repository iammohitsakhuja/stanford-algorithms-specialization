import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class FloydWarshall {
  /** Loads graph from a file. */
  private static Graph loadGraphFromFile(String fileName) {
    Scanner reader = null;

    // Open the file for reading.
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException ex) {
      System.err.println("Error: File not found");
      ex.printStackTrace();
      return null;
    }

    // Get the number of vertices and edges.
    int numVertices = reader.nextInt();
    int numEdges = reader.nextInt();

    // Create a graph.
    Graph graph = new Graph(numVertices);

    // Read the edges and add them to the graph.
    for (int i = 0; i < numEdges && reader.hasNextInt(); i++) {
      int src = reader.nextInt();
      int dest = reader.hasNextInt() ? reader.nextInt() : 0;
      int weight = reader.hasNextInt() ? reader.nextInt() : 0;

      graph.addEdge(src, dest, weight);
    }

    // Housekeeping.
    reader.close();

    return graph;
  }

  /** Computes shortest path distance given all pairs shortest path lengths' matrix. */
  private static long computeShortestDistance(long[][] allPairsShortestPathLengths) {
    long minValue = allPairsShortestPathLengths[0][0];

    for (int i = 0; i < allPairsShortestPathLengths.length; i++)
      for (int j = 0; j < allPairsShortestPathLengths.length; j++)
        if (allPairsShortestPathLengths[i][j] < minValue)
          minValue = allPairsShortestPathLengths[i][j];

    return minValue;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length < 1) {
      System.err.println("Usage: java FloydWarshall <numGraphs> [...fileNames]");
      System.exit(1);
    }

    // Get the inputs.
    int numGraphs = 0;

    try {
      numGraphs = Integer.parseInt(args[0]);
    } catch (NumberFormatException ex) {
      System.err.println("Number of graphs must be an integer");
      System.exit(2);
    }

    // Further ensure proper usage.
    if (args.length != 1 + numGraphs) {
      System.err.println("Must enter the filenames for the specified number of graphs");
      System.exit(3);
    }

    // Get the rest of the inputs.
    String[] fileNames = new String[numGraphs];
    for (int i = 0; i < numGraphs; i++) fileNames[i] = args[1 + i];

    // Load graphs from the given files.
    Graph[] graphs = new Graph[numGraphs];
    for (int i = 0; i < numGraphs; i++) graphs[i] = loadGraphFromFile(fileNames[i]);

    long[][][] allPairsShortestPathLengths = new long[numGraphs][][];

    // Compute all pairs shortest path lengths.
    for (int i = 0; i < numGraphs; i++)
      allPairsShortestPathLengths[i] = graphs[i].getAllPairsShortestPathLengths();

    // Calculate the shortest path distance for each graph and display the result.
    long shortestShortestPathDistance = Long.MAX_VALUE;
    for (int i = 0; i < numGraphs; i++)
      if (allPairsShortestPathLengths[i] == null)
        System.out.printf("Cycle exists for graph %d\n", i + 1);
      else {
        long currShortestDistance = computeShortestDistance(allPairsShortestPathLengths[i]);
        if (currShortestDistance < shortestShortestPathDistance)
          shortestShortestPathDistance = currShortestDistance;

        System.out.printf("Shortest path distance for graph %d: %d\n", i + 1, currShortestDistance);
      }
    System.out.println();

    // Display the final result.
    if (shortestShortestPathDistance != Long.MAX_VALUE)
      System.out.printf("Shortest shortest path distance: %d\n", shortestShortestPathDistance);
    else System.out.println("No shortest shortest path distance for the given graphs!");
  }
}
