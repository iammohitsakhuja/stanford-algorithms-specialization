import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Scanner;

class MaxWeightIndependentSet {

  /** Loads weights of vertices from a file into an array. */
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

  /** Gets the maximum weight independent set from a path graph that has weighted vertices. */
  static HashMap<Integer, Integer> getMaximumWeightIndependentSet(int[] weights) {
    // Array to hold the maximum weights uptil ith vertex of the path graph.
    long[] setWeights = new long[weights.length + 1];

    // Base conditions.
    setWeights[0] = 0;
    setWeights[1] = weights[0];

    // The max weight till any vertex will be the max of:
    // Case 1: If vertex is not in max weight independent set, then max weight till the previous
    // vertex.
    // Case 2: If vertex is in max weight independent set, then max weight till 2nd previous vertex
    // + weight of current vertex.
    for (int i = 1; i < weights.length; i++)
      setWeights[i + 1] = Long.max(setWeights[i], setWeights[i - 1] + weights[i]);

    // Create a hash table to hold each vertex of the max weight independent set, along with its
    // weight.
    HashMap<Integer, Integer> maxWeightIndependentSet = new HashMap<>();

    // Reconstruct the max weight independent set.
    for (int i = setWeights.length - 1; i >= 1; )
      if (setWeights[i] > setWeights[i - 1]) {
        maxWeightIndependentSet.put(i, weights[i - 1]);
        i -= 2;
      } else i -= 1;

    return maxWeightIndependentSet;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java WeightIndependentSet <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Load weights from file.
    int[] weights = loadWeightsFromFile(fileName);

    // Get the max weight independent set.
    HashMap<Integer, Integer> maxWeightIndependentSet = getMaximumWeightIndependentSet(weights);

    // Calculate the sum of the weights of all vertices in the max weight independent set.
    long maxWeightSum = 0;
    for (Iterator<Entry<Integer, Integer>> it = maxWeightIndependentSet.entrySet().iterator();
        it.hasNext(); ) {
      Entry<Integer, Integer> entry = it.next();
      maxWeightSum += entry.getValue();
    }

    System.out.println("Sum of weights in Max Weight Independent Set: " + maxWeightSum);
  }
}
