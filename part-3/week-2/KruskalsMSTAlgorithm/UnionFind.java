class UnionFind {

  // Represents a single subset.
  private class Subset {
    int parent;
    int rank; /* Rank represents maximum depth of tree. */

    Subset(int parent, int rank) {
      this.parent = parent;
      this.rank = rank;
    }
  }

  // All subsets in this Union Find.
  private Subset[] subsets;

  UnionFind(int n) {
    this.subsets = new Subset[n];

    // Initially, all numbers are in their own sets and have rank 1.
    for (int i = 0; i < n; i++) this.subsets[i] = new Subset(i, 1);
  }

  int find(int x) {
    // Do path compression during finding.
    if (this.subsets[x].parent != x) this.subsets[x].parent = this.find(this.subsets[x].parent);

    return this.subsets[x].parent;
  }

  void union(int x, int y) {
    int parentX = this.find(x);
    int parentY = this.find(y);

    if (parentX == parentY) return;

    // Union by rank.
    if (this.subsets[parentX].rank < this.subsets[parentY].rank)
      this.subsets[parentX].parent = parentY;
    else {
      this.subsets[parentY].parent = parentX;
      if (this.subsets[parentX].rank == this.subsets[parentY].rank) this.subsets[parentX].rank++;
    }
  }
}
