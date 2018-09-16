import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

class Tree {
  class TreeNode implements Comparable<TreeNode> {
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

  TreeNode root;

  Tree(int[] weights) {
    this.root = null;
    PriorityQueue<TreeNode> heap = new PriorityQueue<TreeNode>(weights.length);

    for (int weight : weights) heap.add(new TreeNode(weight, null, null));

    while (heap.size() > 1) {
      TreeNode first = heap.poll();
      TreeNode second = heap.poll();

      heap.add(new TreeNode(first.weight + second.weight, first, second));
    }

    this.root = heap.poll();
  }

  int getMaximumLength() {

    Queue<TreeNode> nodes = new LinkedList<TreeNode>();

    nodes.add(this.root);
    nodes.add(null);

    // Start from 0 as maximum length of codeword will be 1 less than the maximum depth of the tree.
    int countLevels = 0;

    while (!nodes.isEmpty()) {
      TreeNode currNode = nodes.poll();

      if (currNode == null) {
        if (!nodes.isEmpty()) {
          nodes.add(null);
          countLevels++;
          continue;
        } else break;
      }

      if (currNode.left != null) nodes.add(currNode.left);

      if (currNode.right != null) nodes.add(currNode.right);
    }

    return countLevels;
  }

  int getMinimumLength() {

    Queue<TreeNode> nodes = new LinkedList<TreeNode>();

    nodes.add(this.root);
    nodes.add(null);

    // Start from 0 as minimum length of codeword will be 1 less than the minimum depth of the tree.
    int countLevels = 0;

    while (!nodes.isEmpty()) {
      TreeNode currNode = nodes.poll();

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

      if (!hasAChild) break;
    }

    return countLevels;
  }
}
