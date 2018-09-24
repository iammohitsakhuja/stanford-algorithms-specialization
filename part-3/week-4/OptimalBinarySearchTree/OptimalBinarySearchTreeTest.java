class OptimalBinarySearchTreeTest {
  private static void test() {
    assert new OptimalBinarySearchTree(new int[] {20, 12, 10}, new int[] {50, 8, 34})
            .getOptimalBSTCost()
        == 142;
    assert new OptimalBinarySearchTree(new int[] {10, 12}, new int[] {34, 50}).getOptimalBSTCost()
        == 118;
  }

  public static void main(String[] args) {
    test();
    System.out.println("All tests passed!");
  }
}
