# Breadth First Search

## Overview

This folder contains a program that implements the Breadth First Search
algorithm for traversing and printing the nodes of a graph.

### Execution steps

To run and view it for yourself, follow these steps:

```bash
$ make
$ ./bfs
Enter number of vertices: 7
Enter number of edges: 9
Enter v, w: 0 1
Enter v, w: 0 2
Enter v, w: 1 3
Enter v, w: 2 3
Enter v, w: 2 4
Enter v, w: 3 5
Enter v, w: 4 5
Enter v, w: 4 6
Enter v, w: 5 6
Enter the edge number from where to start the BFS, s: 0
0 2 1 4 3 6 5
```

**Note:** The vertices are numbered [0, n). And the graph implemented here is
undirected. The output above is for the following graph:

    0 ----- 1 ----- 3 ----- 5 ------
    |               |       |       |
    |               |       |       |
    |               |       |       |
     -------------- 2 ----- 4 ----- 6
