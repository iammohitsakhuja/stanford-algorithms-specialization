import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class HuffmanCoding {
  /** Loads weights from a file into an array. */
  static int[] loadWeightsFromFile(String fileName) {
    Scanner reader = null;

    // Open the file for reading.
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException e) {
      System.err.println("Error: File not found");
      e.printStackTrace();
      return null;
    }

    // Get the total number of weights.
    int numWeights = reader.hasNextInt() ? reader.nextInt() : 0;

    // Read the weights from the file.
    int[] weights = new int[numWeights];
    for (int i = 0; i < numWeights; i++) weights[i] = reader.hasNextInt() ? reader.nextInt() : 0;

    // Housekeeping.
    reader.close();

    return weights;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java HuffmanCoding <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Benchmarks.
    double timeLoadingWeights = 0.0;
    double timeBuildingTreeFromQueue = 0.0;
    double timeBuildingTreeFromHeap = 0.0;

    // Load weights from the given file and benchmark the time taken.
    long startTime = System.nanoTime();
    int[] weights = loadWeightsFromFile(fileName);
    timeLoadingWeights = (System.nanoTime() - startTime) / 1000000.0;
    if (weights == null) {
      System.err.println("Could not load weights");
      System.exit(2);
    }

    // Build Huffman tree by using 2 queues and benchmark the time taken.
    startTime = System.nanoTime();
    Tree huffmanTreeFromQueue = new Tree(weights);
    timeBuildingTreeFromQueue = (System.nanoTime() - startTime) / 1000000.0;

    // Build Huffman tree by using a heap and benchmark the time taken.
    startTime = System.nanoTime();
    Tree huffmanTreeFromHeap = new Tree(weights, true);
    timeBuildingTreeFromHeap = (System.nanoTime() - startTime) / 1000000.0;

    // Display the Maximum and Minimum Length of codewords.
    System.out.printf(
        "Maximum length of codeword (queue): %2d\n", huffmanTreeFromQueue.getMaximumLength());
    System.out.printf(
        "Minimum length of codeword (queue): %2d\n\n", huffmanTreeFromQueue.getMinimumLength());

    System.out.printf(
        "Maximum length of codeword (heap): %3d\n", huffmanTreeFromHeap.getMaximumLength());
    System.out.printf(
        "Minimum length of codeword (heap): %3d\n\n", huffmanTreeFromHeap.getMinimumLength());

    // Display the benchmark results.
    System.out.printf("TIME IN loading weights:             %6.2fms\n", timeLoadingWeights);
    System.out.printf("TIME IN building tree from 2 queues: %6.2fms\n", timeBuildingTreeFromQueue);
    System.out.printf("TIME IN building tree from heap:     %6.2fms\n", timeBuildingTreeFromHeap);
    System.out.printf(
        "TIME IN total:                       %6.2fms\n",
        timeLoadingWeights + timeBuildingTreeFromQueue + timeBuildingTreeFromHeap);
  }
}
