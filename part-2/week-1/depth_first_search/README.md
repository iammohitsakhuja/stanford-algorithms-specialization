# Depth First Search

## Overview

This folder contains a program that implements the Depth First Search
algorithm for traversing a graph.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./dfs
First cluster found!
Second cluster found!
Third cluster found!
First set of tests passed!

Full graph traversed!
Second set of tests passed!

All tests passed!
```

**Note:** The vertices are numbered [1, n]. And the graph implemented here is
undirected. The program has been tested for the following 2 graphs:

##### Graph 1

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

##### Graph 2

                          2 --------- 4 --------- 6
                        /           /           / |
                      /           /           /   |
                    1           /           /     |
                      \       /           /       |
                        \   /           /         |
                          3 --------- 5 --------- 7

