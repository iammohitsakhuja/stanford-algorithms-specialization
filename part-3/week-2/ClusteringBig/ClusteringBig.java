import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

class ClusteringBig {
  /** Loads the labels of vertices from a file. */
  private static String[] loadLabelsFromFile(String fileName) {
    Scanner reader = null;

    // Open the file for reading.
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException e) {
      System.err.println("Error: File not found");
      e.printStackTrace();
      return null;
    }

    // Get the number of vertices.
    int numVertices = reader.hasNextInt() ? reader.nextInt() : 0;
    int numBits = reader.hasNextInt() ? reader.nextInt() : 1;

    // Clear buffer till end of line.
    reader.nextLine();

    // List of all labels.
    String[] labels = new String[numVertices];

    for (int i = 0; i < numVertices; i++) {
      // Read a line and get its characters.
      String line = reader.nextLine();
      char[] characters = line.toCharArray();

      // Remove all spaces from the line.
      StringBuilder sb = new StringBuilder();
      for (char c : characters) if (!Character.isSpaceChar(c)) sb.append(c);

      // Add the label to the list of our labels.
      labels[i] = sb.toString();
    }

    // Housekeeping.
    reader.close();

    return labels;
  }

  /** Get only the unique labels. */
  private static ArrayList<String> getUniqueLabels(String fileName) {
    // Load labels from the file.
    String[] labels = loadLabelsFromFile(fileName);

    // Sort the labels.
    Arrays.sort(labels);

    // Create an arraylist to hold only the unique labels.
    ArrayList<String> uniqueLabels = new ArrayList<>();

    // Clear out the duplicates.
    uniqueLabels.add(labels[0]);

    for (int i = 1; i < labels.length; i++) {
      while (labels[i].equals(labels[i - 1])) i++;
      uniqueLabels.add(labels[i]);
    }

    return uniqueLabels;
  }

  /** Returns the total number of combinations when choosing k elements out of n. */
  private static int getNChooseK(int n, int k) {
    int result = 1;

    for (int i = 0; i < k; i++) result = (result * (n - i)) / (i + 1);

    return result;
  }

  /** Returns the inverted character (0 or 1) for the given character. */
  private static char invertBit(char bit) throws IllegalArgumentException {
    switch (bit) {
      case '0':
        return '1';
      case '1':
        return '0';
      default:
        throw new IllegalArgumentException();
    }
  }

  /** Utility function for generating inverted permutations of a binary string. */
  private static void generateCombinationsUtil(
      char[] characters, int startIndex, int bitsToInvert, ArrayList<String> combinations) {
    if (bitsToInvert == 0) return;

    for (int i = startIndex; i <= characters.length - bitsToInvert; i++) {
      // Invert the bit at current position.
      characters[i] = invertBit(characters[i]);

      // Generate combinations starting from the next index but with one less bit inverted.
      generateCombinationsUtil(characters, i + 1, bitsToInvert - 1, combinations);

      // Add to the list of combinations.
      if (bitsToInvert == 1) combinations.add(new String(characters));

      // Invert back the bit at the current position.
      characters[i] = invertBit(characters[i]);
    }
  }

  /** Generates inverted permutations of a binary string with `k` bits inverted. */
  private static ArrayList<String> generateCombinations(String string, int k) {
    // Calculate the total number of combinations that can be produced.
    int totalCombos = getNChooseK(string.length(), k);

    // Create a list for holding the combinations.
    ArrayList<String> combinations = new ArrayList<String>(totalCombos);

    // Generate the combinations.
    generateCombinationsUtil(string.toCharArray(), 0, k, combinations);

    return combinations;
  }

  private static int getMaxClusters(ArrayList<String> vertices) {
    // Hash all labels.
    HashMap<String, Integer> hashTable = new HashMap<String, Integer>(vertices.size());

    for (int i = 0; i < vertices.size(); i++) hashTable.put(vertices.get(i), i);

    // Initialize a UnionFind.
    UnionFind uf = new UnionFind(vertices.size());

    int numClusters = vertices.size();

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < vertices.size(); j++) {
        ArrayList<String> combinations = generateCombinations(vertices.get(j), i + 1);

        for (String combo : combinations) {
          if (hashTable.containsKey(combo)) {
            int vertex = hashTable.get(combo);

            if (uf.find(j) != uf.find(vertex)) {
              numClusters--;
              uf.union(j, vertex);
            }
          }
        }
      }
    }

    return numClusters;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java ClusteringBig <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Get the labels.
    ArrayList<String> labels = getUniqueLabels(fileName);

    // Get the max number of clusters for a given k.
    int maxClusters = getMaxClusters(labels);
    System.out.println("Max clusters: " + maxClusters);
  }
}
