import java.util.Arrays;

class OptimalBinarySearchTree {
  /** Represents a tree node. */
  static class TreeNode implements Comparable<TreeNode> {
    int key;
    int frequency;

    TreeNode(int key, int frequency) {
      this.key = key;
      this.frequency = frequency;
    }

    @Override
    public int compareTo(TreeNode treeNode) {
      return this.key - treeNode.key;
    }

    @Override
    public String toString() {
      return this.key + " " + this.frequency;
    }
  }

  TreeNode[] nodes;

  OptimalBinarySearchTree(int[] keys, int[] frequencies) {
    assert keys.length == frequencies.length;

    // Get the tree nodes.
    this.nodes = new TreeNode[keys.length];
    for (int i = 0; i < keys.length; i++) nodes[i] = new TreeNode(keys[i], frequencies[i]);

    // Sort them in increasing order of their keys.
    Arrays.sort(this.nodes);
  }

  // Helper function for finding sum of frequencies between a given range.
  private int findSum(int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) sum += this.nodes[i].frequency;
    return sum;
  }

  /** Get optimal BST cost. */
  int getOptimalBSTCost() {
    int[][] lookupTable = new int[this.nodes.length][this.nodes.length];

    // Represents A[i, i] = frequency[i].
    for (int i = 0; i < this.nodes.length; i++) lookupTable[i][i] = this.nodes[i].frequency;

    for (int size = 1; size < this.nodes.length; size++) {
      for (int i = 0; i < this.nodes.length - size; i++) {
        // Find the sum of frequencies in the current range.
        int sum = this.findSum(i, i + size);

        int min = Integer.min(lookupTable[i + 1][i + size], lookupTable[i][i + size - 1]);
        for (int r = i + 1; r < i + size; r++)
          min = Integer.min(min, lookupTable[i][r - 1] + lookupTable[r + 1][i + size]);

        lookupTable[i][i + size] = sum + min;
      }
    }

    return lookupTable[0][this.nodes.length - 1];
  }
}
