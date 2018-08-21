# Topological Sort using DFS

## Overview

This folder contains a program that sorts the vertices of a directed graph in a
topological manner i.e. for every pair of vertices (u, v) of a directed edge,
the f-value of the vertex at the tail of the edge, u is less than the f-value
of the vertex at the head of that edge, v.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./topological_sort
Vertices have been sorted topologically!
All tests passed!
```

**Note:** The vertices are numbered [1, n]. And the graph implemented here is
directed. The program has been tested for the following graph:

            ---> 2 <---
          /             \
        5                 \
          \                 \
            ---> 1       ---> 4
          /            /
        6            /
          \        /
            ---> 3
