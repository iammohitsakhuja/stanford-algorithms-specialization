# Graph Operations

## Overview

This folder contains a program that implements the following graph operations:

- Breadth First Search
- Finding shortest path between two vertices
- Computing Connected Components of a graph
- Depth First Search
- Topological Sort
- Computing Strongly Components in a directed graph

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
c++ -std=c++17   -c -o main.o main.cc
c++ -std=c++17   -c -o Graph.o Graph.cc
c++ -std=c++17   -c -o Vertex.o Vertex.cc
c++ -std=c++17   -c -o tests.o tests.cc
c++ -std=c++17   -c -o benchmark.o benchmark.cc
c++ -std=c++17 -o graph_operations main.o Graph.o Vertex.o tests.o benchmark.o
$ unzip SCC.zip
Archive:  SCC.zip
  inflating: SCC.txt
$ cat SCC.txt | ./graph_operations 875714 5105043
BFS tests passed!
Shortest path tests passed!
Connected components tests passed!
DFS tests passed!
Topological sort tests passed!
Reversing tests passed!
All tests passed!

SCCs computed successfully!
The sizes of the largest (at most 5) SCCs are: 434821 968 459 314 211
TIME in computing SCCs:  3.98s
```

**Note:** The file `SCC.txt` has been provided here, and is needed for the
program to run. It is where the numbers `875714` and `5105043` come from, the
former represents the number of vertices and the latter represents the number
of lines/edges. These can be changed according to your needs or according to
the file you provide.

**Note:** The vertices are numbered [1, n] and the edges are undirected for
every operation excluding computing SCCs.

### Graphs Used

The following graphs have been used for testing purposes:

#### Breadth First Search

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

#### Shortest Path using BFS

               2 --- 4 --- 9                             5
              /     /|    /                            / |
             /     / |   /                            /  |
            1     /  |  /                            3   |   10
             \   /   | /                              \  |  /
              \ /    |/                                \ | /
               6 --- 7                                   8

#### Connected Components using BFS

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

#### Depth First Search

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

#### Topological Sort using DFS

                              ---> 2 <---
                            /             \
                          5                 \
                            \                 \
                              ---> 1       ---> 4
                            /            /
                          6            /
                            \        /
                              ---> 3

