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

  private static int getNChooseK(int n, int k) {
    int result = 1;

    for (int i = 0; i < k; i++) result = (result * (n - i)) / (i + 1);

    return result;
  }

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

  private static void generateCombos(
      char[] characters, int startIndex, int bitsToInvert, String[] combos) {
    if (bitsToInvert == 0) return;

    for (int i = startIndex; i <= characters.length - bitsToInvert; i++) {
      // Invert the bit at current position.
      characters[i] = invertBit(characters[i]);

      // Make a recursive call.
      generateCombos(characters, i + 1, bitsToInvert - 1, combos);

      // Add to combos.
      if (bitsToInvert == 1) combos[resultIndex++] = new String(characters);

      // Invert back.
      characters[i] = invertBit(characters[i]);
    }
  }

  private static int resultIndex = 0;

  private static String[] wrapper(String string, int k) {
    int totalCombos = getNChooseK(string.length(), k);

    String[] combos = new String[totalCombos];

    resultIndex = 0;

    generateCombos(string.toCharArray(), 0, k, combos);

    resultIndex = 0;

    return combos;
  }

  private static int getMaxClusters(ArrayList<String> vertices) {
    // Hash all labels.
    HashMap<String, Integer> hashTable = new HashMap<String, Integer>(vertices.size());

    for (int i = 0; i < vertices.size(); i++) hashTable.put(vertices.get(i), i);

    // Initialize a UnionFind.
    UnionFind uf = new UnionFind(vertices.size());

    int numClusters = vertices.size();
    for (int i = 0; i < vertices.size(); i++) {
      String[] combinations = wrapper(vertices.get(i), 1);

      for (String combo : combinations) {
        if (hashTable.containsKey(combo)) {
          int vertex = hashTable.get(combo);

          if (uf.find(i) != uf.find(vertex)) {
            numClusters--;
            uf.union(i, vertex);
          }
        }
      }
    }
    for (int i = 0; i < vertices.size(); i++) {
      String[] combinations = wrapper(vertices.get(i), 2);

      for (String combo : combinations) {
        if (hashTable.containsKey(combo)) {
          int vertex = hashTable.get(combo);

          if (uf.find(i) != uf.find(vertex)) {
            numClusters--;
            uf.union(i, vertex);
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
