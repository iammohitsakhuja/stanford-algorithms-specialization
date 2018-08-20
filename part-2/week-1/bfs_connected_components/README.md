# Connected Components using BFS

## Overview

This folder contains a program that finds the connected components of a graph
using Breadth First Search.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./connected_components
Component 1 tests passed!
Component 2 tests passed!
Component 3 tests passed!

All tests passed!
```

**Note:** The vertices are numbered [1, n]. And the graph implemented here is
undirected. The program has been tested for the following graph:

        1 --------- 3
         \         /
          \       /                                             6
           \     /                                             / \
            \   /                                             /   \
              5                2 --------- 4                 /     \
            /   \                                           8      10
           /     \
          /       \
         /         \
        7 --------- 9

