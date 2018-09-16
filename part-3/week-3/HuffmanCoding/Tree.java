import java.util.Arrays;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

class Tree {
  /** Represents a single node of a Huffman Tree. */
  static class TreeNode implements Comparable<TreeNode> {
    int weight;
    TreeNode left;
    TreeNode right;

    TreeNode(int weight, TreeNode left, TreeNode right) {
      this.weight = weight;
      this.left = left;
      this.right = right;
    }

    public int compareTo(TreeNode treeNode) {
      return this.weight - treeNode.weight;
    }
  }

  // Root of the given tree.
  TreeNode root;

  /** Constructors. */
  Tree(int[] weights) {
    this.root = buildHuffmanTreeWithQueues(weights);
  }

  Tree(int[] weights, boolean useHeap) {
    if (useHeap) {
      this.root = buildHuffmanTreeWithHeap(weights);
      return;
    }

    this.root = buildHuffmanTreeWithQueues(weights);
  }

  private static TreeNode buildHuffmanTreeWithQueues(int[] weights) {
    // Sort the weights in increasing order.
    Arrays.sort(weights);

    // Create two queues.
    // First queue will hold the actual nodes with their weights.
    Queue<TreeNode> firstQueue = new LinkedList<TreeNode>();
    // Second queue will hold the merged nodes with the new weights.
    Queue<TreeNode> secondQueue = new LinkedList<TreeNode>();

    // Add all individual weights to the first queue.
    for (int weight : weights) firstQueue.add(new TreeNode(weight, null, null));

    while (!firstQueue.isEmpty() || secondQueue.size() > 1) {
      // Get the 2 nodes with minimum weights.
      TreeNode first = getNodeWithMinimumWeight(firstQueue, secondQueue);
      TreeNode second = getNodeWithMinimumWeight(firstQueue, secondQueue);

      // Merge them into one node and add it to the end of the second queue.
      secondQueue.add(new TreeNode(first.weight + second.weight, first, second));
    }

    // The last remaining node is the root of the tree.
    return secondQueue.poll();
  }

  private static TreeNode buildHuffmanTreeWithHeap(int[] weights) {
    // Create a Min Priority Queue to hold the tree nodes.
    PriorityQueue<TreeNode> heap = new PriorityQueue<TreeNode>(weights.length);

    // Add all weights to the priority queue.
    for (int weight : weights) heap.add(new TreeNode(weight, null, null));

    while (heap.size() > 1) {
      // Get the 2 nodes with the minimum weights.
      TreeNode first = heap.poll();
      TreeNode second = heap.poll();

      // Merge them into one node and add it to the priority queue.
      heap.add(new TreeNode(first.weight + second.weight, first, second));
    }

    // The last remaining node is the root of the tree.
    return heap.poll();
  }

  /** Gets the node with minimum weight from 2 queues. */
  private static TreeNode getNodeWithMinimumWeight(
      Queue<TreeNode> firstQueue, Queue<TreeNode> secondQueue) throws IllegalArgumentException {

    if (firstQueue.isEmpty() && secondQueue.isEmpty()) throw new IllegalArgumentException();

    if (firstQueue.isEmpty()) return secondQueue.poll();

    if (secondQueue.isEmpty()) return firstQueue.poll();

    if (firstQueue.peek().weight < secondQueue.peek().weight) return firstQueue.poll();

    return secondQueue.poll();
  }

  /** Get the maximum length of a codeword. */
  int getMaximumLength() {
    // Queue to hold unprocessed nodes.
    Queue<TreeNode> nodes = new LinkedList<TreeNode>();

    // Add the nodes from the first level of the tree.
    nodes.add(this.root);
    nodes.add(null);

    // Start from 0 as maximum length of codeword will be 1 less than the maximum depth of the tree.
    int countLevels = 0;

    // Traverse in Level Order fashion to get the max length.
    while (!nodes.isEmpty()) {
      TreeNode currNode = nodes.poll();

      // Add `null` after complete traversal of one level.
      if (currNode == null) {
        if (nodes.isEmpty()) break;

        nodes.add(null);
        countLevels++;
        continue;
      }

      if (currNode.left != null) nodes.add(currNode.left);
      if (currNode.right != null) nodes.add(currNode.right);
    }

    return countLevels;
  }

  /** Get the minimum length of a codeword. */
  int getMinimumLength() {
    // Queue to hold unprocessed nodes.
    Queue<TreeNode> nodes = new LinkedList<TreeNode>();

    // Add the nodes from the first level of the tree.
    nodes.add(this.root);
    nodes.add(null);

    // Start from 0 as minimum length of codeword will be 1 less than the minimum depth of the tree.
    int countLevels = 0;

    // Traverse in Level Order fashion to get the min length.
    while (!nodes.isEmpty()) {
      TreeNode currNode = nodes.poll();

      // Add `null` after complete traversal of one level.
      if (currNode == null) {
        if (nodes.isEmpty()) break;

        nodes.add(null);
        countLevels++;
        continue;
      }

      boolean hasAChild = false;

      if (currNode.left != null) {
        hasAChild = true;
        nodes.add(currNode.left);
      }

      if (currNode.right != null) {
        hasAChild = true;
        nodes.add(currNode.right);
      }

      // If the current node has no child, then it has the minimum length.
      if (!hasAChild) break;
    }

    return countLevels;
  }
}
