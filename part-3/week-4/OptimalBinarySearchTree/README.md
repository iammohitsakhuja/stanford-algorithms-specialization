# Optimal Binary Search Tree

## Overview

This folder contains a program that implements the DP solution of the Optimal
BST program that given a list of keys and their frequencies, finds the optimal
way of constructing a BST out of them.

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java -ea OptimalBinarySearchTreeTest
All tests passed!
```

**Disclaimer:** The actual output cost of the keys is not shown. Instead, the
program contains tests for two sets of keys and their frequencies that are
shown below. These test cases have been taken from
[GeeksForGeeks](https://www.geeksforgeeks.org/optimal-binary-search-tree-dp-24/).

## Test Cases

### Test case I

- Keys: `[20, 12, 10]`
- Frequencies: `[50, 8, 34]`
- Expected cost: 142

### Test Case II

- Keys: `[10, 12]`
- Frequencies: `[50, 8, 34]`
- Expected cost: 118
