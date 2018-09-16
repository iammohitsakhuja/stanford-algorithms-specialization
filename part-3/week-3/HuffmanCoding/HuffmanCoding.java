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

    // Load weights from the given file.
    int[] weights = loadWeightsFromFile(fileName);
    if (weights == null) {
      System.err.println("Could not load weights");
      System.exit(2);
    }

    // Build Huffman tree.
    Tree huffmanTreeFromQueue = new Tree(weights);
    Tree huffmanTreeFromHeap = new Tree(weights, true);

    System.out.println(huffmanTreeFromQueue.getMaximumLength());
    System.out.println(huffmanTreeFromQueue.getMinimumLength());

    System.out.println(huffmanTreeFromHeap.getMaximumLength());
    System.out.println(huffmanTreeFromHeap.getMinimumLength());
  }
}
