# Breadth First Search

## Overview

This folder contains a program that implements the Breadth First Search
algorithm for traversing a graph.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./bfs
First cluster found!
Second cluster found!
Third cluster found!
All tests passed!
```

**Note:** The vertices are numbered [1, n]. And the graph implemented here is
undirected. The program has been tested for the following graph:

        1 --------- 3
         \         /
          \       /                                             4
           \     /                                             / \
            \   /                                             /   \
              5                2 --------- 6                 /     \
            /   \                                           7      10
           /     \
          /       \
         /         \
        8 --------- 9

