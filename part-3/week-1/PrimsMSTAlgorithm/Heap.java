import java.util.ArrayList;
import java.util.Collections;

class Heap {
  private ArrayList<HeapNode> container;
  Integer[] mapping;

  Heap(int n) {
    this.container = new ArrayList<HeapNode>();
    this.mapping = new Integer[n];
  }

  boolean isEmpty() {
    return this.container.isEmpty();
  }

  int size() {
    return this.container.size();
  }

  HeapNode top() {
    return this.container.get(0);
  }

  void push(HeapNode node) {
    // Set appropriate mapping for the incoming node.
    this.mapping[node.getHead()] = this.size();

    // Add the node to the heap.
    this.container.add(node);

    // Bubble the node up to restore heap property.
    this.bubbleUp(this.size() - 1);
  }

  void pop() {
    // Set the mapping of the topmost element to be -1, and the last element to be 0.
    this.mapping[this.container.get(0).getHead()] = -1;
    this.mapping[this.container.get(this.size() - 1).getHead()] = 0;

    // Now swap the first element of the heap with the last.
    Collections.swap(this.container, 0, this.size() - 1);

    // Then, remove the last element.
    this.container.remove(this.size() - 1);

    // Bubble the first element down.
    this.bubbleDown(0);
  }

  HeapNode getElementWithKey(int key) {
    return this.container.get(this.mapping[key]);
  }

  void deleteElementWithKey(int key) {
    // Get the index at which the element with this key is present.
    int index = this.mapping[key];

    // If the element is present at the last index, then simply remove it.
    if (index == this.size() - 1) {
      this.mapping[key] = -1;

      this.container.remove(this.size() - 1);
      return;
    }

    // Set the mapping of the element with the given key to be -1, and that of the last element to
    // be the index at which this element is present.
    this.mapping[key] = -1;
    this.mapping[this.container.get(this.size() - 1).getHead()] = index;

    // Now swap the element with the given key with the last element in the heap.
    Collections.swap(this.container, index, this.size() - 1);

    // Then, remove the last element.
    this.container.remove(this.size() - 1);

    // Depending upon the value of the last element that has now been swapped somewhere in the
    // middle, bubble it up or down if necessary.
    if (comparator(this.parent(index), this.container.get(index))) this.bubbleUp(index);
    else this.bubbleDown(index);
  }

  boolean isHeap() {
    for (int i = 0; i < this.size(); i++) {
      if (this.hasLeftChild(i) && comparator(this.container.get(i), this.leftChild(i)))
        return false;

      if (this.hasRightChild(i) && comparator(this.container.get(i), this.rightChild(i)))
        return false;
    }

    return true;
  }

  private void bubbleUp(int index) {
    while (this.hasParent(index) && comparator(this.parent(index), this.container.get(index))) {
      // Get parent index.
      int parentIndex = getParentIndex(index);

      // Make appropriate swaps.
      swap(this.mapping, this.parent(index).getHead(), this.container.get(index).getHead());
      Collections.swap(this.container, parentIndex, index);

      // Update index.
      index = parentIndex;
    }
  }

  private void bubbleDown(int index) {
    while (this.hasLeftChild(index)) {
      // Get the swappable index i.e. the index at which the element is more preferable to be
      // swapped with the element at the given index.
      int swappableIndex = getLeftChildIndex(index);

      if (this.hasRightChild(index) && comparator(this.leftChild(index), this.rightChild(index)))
        swappableIndex = getRightChildIndex(index);

      // If the element at the current index needs to be swapped, then swap it.
      if (comparator(this.container.get(index), this.container.get(swappableIndex))) {
        swap(
            this.mapping,
            this.container.get(index).getHead(),
            this.container.get(swappableIndex).getHead());
        Collections.swap(this.container, index, swappableIndex);

        // Update the index.
        index = swappableIndex;
      } else break;
    }
  }

  private static boolean comparator(HeapNode a, HeapNode b) {
    return a.getWeight() > b.getWeight();
  }

  private static <T> void swap(T[] array, int index1, int index2) {
    T temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
  }

  /** Helper functions. */
  /** Get indices. */
  private static int getLeftChildIndex(int index) {
    return 2 * index + 1;
  }

  private static int getRightChildIndex(int index) {
    return 2 * (index + 1);
  }

  private static int getParentIndex(int index) {
    return (index - 1) / 2;
  }

  /** Check parent/child exists for a given index. */
  private boolean hasLeftChild(int index) {
    return getLeftChildIndex(index) < this.size();
  }

  private boolean hasRightChild(int index) {
    return getRightChildIndex(index) < this.size();
  }

  private boolean hasParent(int index) {
    return getParentIndex(index) >= 0;
  }

  /** Get child/parent node for a given index. */
  private HeapNode leftChild(int index) {
    return this.container.get(getLeftChildIndex(index));
  }

  private HeapNode rightChild(int index) {
    return this.container.get(getRightChildIndex(index));
  }

  private HeapNode parent(int index) {
    return this.container.get(getParentIndex(index));
  }
}
