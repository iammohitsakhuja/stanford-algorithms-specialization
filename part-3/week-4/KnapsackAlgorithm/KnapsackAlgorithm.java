import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Scanner;

class KnapsackAlgorithm {
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

  private static int[][] getLookupTable(Knapsack knapsack) {
    // Create a lookup table of size (numItems + 1) * (maxWeight + 1).
    int[][] lookupTable = new int[knapsack.items.length + 1][knapsack.maxWeight + 1];

    for (int i = 1; i < lookupTable.length; i++) {
      int currWeight = knapsack.items[i - 1].weight;
      int currValue = knapsack.items[i - 1].value;

      // For weights that are less than the weight of the current item, the value will be inherited
      // from the previous row.
      for (int w = 0; w < currWeight; w++) lookupTable[i][w] = lookupTable[i - 1][w];

      // Fill the rest of the table.
      for (int w = currWeight; w < lookupTable[i].length; w++)
        lookupTable[i][w] =
            Integer.max(lookupTable[i - 1][w], currValue + lookupTable[i - 1][w - currWeight]);
    }

    return lookupTable;
  }

  private static LinkedList<Item> reconstructListOfItems(int[][] lookupTable, Knapsack knapsack) {
    // Create a linked list to store the list of items to be stored in the knapsack.
    LinkedList<Item> bestKnapsackItems = new LinkedList<>();

    for (int i = lookupTable.length - 1, residualWeight = knapsack.maxWeight;
        i > 0 && residualWeight > 0;
        i--) {
      int currWeight = knapsack.items[i - 1].weight;
      int currValue = knapsack.items[i - 1].value;

      // Do not include the current item if its weight is less than the remaining weight.
      if (currWeight > residualWeight) continue;

      // Condition when the current item will be included.
      if (currValue + lookupTable[i - 1][residualWeight - currWeight]
          > lookupTable[i - 1][residualWeight]) {
        bestKnapsackItems.push(knapsack.items[i - 1]);
        residualWeight -= currWeight;
      }
    }

    return bestKnapsackItems;
  }

  static LinkedList<Item> getBestKnapsackItems(Knapsack knapsack) {
    // Get a lookup table for the knapsack.
    int[][] lookupTable = getLookupTable(knapsack);

    // Return the list of items to be included in the knapsack.
    return reconstructListOfItems(lookupTable, knapsack);
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java KnapsackAlgorithm <fileName>");
      System.exit(1);
    }

    // Get the inputs.
    String fileName = args[0];

    // Load the knapsack instance from the file.
    Knapsack knapsack = loadKnapsackFromFile(fileName);

    // Get the list of the best valued items that should be included in the knapsack.
    LinkedList<Item> bestKnapsackItems = getBestKnapsackItems(knapsack);

    // Calculate the total value of all items in the knapsack.
    int sum = 0;
    for (Item item : bestKnapsackItems) sum += item.value;

    // Display the results.
    System.out.printf("Number of items in the knapsack: %7d\n", bestKnapsackItems.size());
    System.out.printf("Sum of values in the knapsack:   %7d\n", sum);
  }
}
