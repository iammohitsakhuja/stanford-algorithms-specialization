import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class KnapsackBig {
  static class Item {
    int value;
    int weight;

    Item(int value, int weight) {
      this.value = value;
      this.weight = weight;
    }
  }

  static class Knapsack {
    Item[] items;
    int maxWeight;

    Knapsack(int maxWeight, Item[] items) {
      this.maxWeight = maxWeight;
      this.items = items;
    }
  }

  static Knapsack loadKnapsackFromFile(String fileName) {
    Scanner reader = null;

    // Open the file for reading.
    try {
      reader = new Scanner(new File(fileName));

    } catch (FileNotFoundException e) {
      System.err.println("Error: File not found");
      e.printStackTrace();
      return null;
    }

    // Get the max weight of the knapsack and the number of items in it.
    int maxWeight = reader.hasNextInt() ? reader.nextInt() : 0;
    int numItems = reader.hasNextInt() ? reader.nextInt() : 0;

    Item[] items = new Item[numItems];

    // Read each item's value and weight.
    for (int i = 0; i < numItems; i++) {
      int value = reader.hasNextInt() ? reader.nextInt() : 0;
      int weight = reader.hasNextInt() ? reader.nextInt() : 0;

      items[i] = new Item(value, weight);
    }

    // Housekeeping.
    reader.close();

    return new Knapsack(maxWeight, items);
  }

  static int getBestKnapsackValue(Knapsack knapsack) {
    // Create a lookup table with just 2 rows that are needed.
    int[][] lookupTable = new int[2][knapsack.maxWeight + 1];

    for (int i = 0, x = 0, y = 1;
        i < knapsack.items.length;
        i++, x = (x + 1) % 2, y = (y + 1) % 2) {

      int currWeight = knapsack.items[i].weight;
      int currValue = knapsack.items[i].value;

      // For weights that are less than the weight of the current item, the value will be inherited
      // from the previous row.
      for (int w = 0; w < currWeight; w++) lookupTable[x][w] = lookupTable[y][w];

      // Fill the rest of the table.
      for (int w = currWeight; w < lookupTable[x].length; w++)
        lookupTable[x][w] =
            Integer.max(lookupTable[y][w], currValue + lookupTable[y][w - currWeight]);
    }

    return Integer.max(lookupTable[0][knapsack.maxWeight], lookupTable[1][knapsack.maxWeight]);
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java KnapsackBig <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Benchmarks.
    double timeLoadingKnapsack = 0.0;
    double timeCalculatingBestValue = 0.0;

    // Load the knapsack instance from the file and benchmark the time taken.
    long startTime = System.nanoTime();
    Knapsack knapsack = loadKnapsackFromFile(fileName);
    timeLoadingKnapsack = (System.nanoTime() - startTime) / 1000000000.0;

    // Get the value of the best items that should be included in the knapsack and benchmark the
    // time taken.
    startTime = System.nanoTime();
    int bestKnapsackValue = getBestKnapsackValue(knapsack);
    timeCalculatingBestValue = (System.nanoTime() - startTime) / 1000000000.0;

    // Display the result.
    System.out.println("Best value: " + bestKnapsackValue + "\n");

    // Display the benchmarks.
    System.out.printf(
        "TIME IN loading the knapsack items from the file: %5.3fs\n", timeLoadingKnapsack);
    System.out.printf(
        "TIME IN calculating best value:                   %5.3fs\n", timeCalculatingBestValue);
    System.out.printf(
        "TIME IN total:                                    %5.3fs\n",
        timeLoadingKnapsack + timeCalculatingBestValue);
  }
}
