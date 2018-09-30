# Floyd-Warshall Algorithm

## Overview

This folder contains a program that implements the Floyd-Warshall Algorithm for
finding All Pairs Shortest Paths Distances in a directed weighted graph.

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java FloydWarshall 3 ../g1.txt ../g2.txt ../g3.txt
Cycle exists for graph 1
Cycle exists for graph 2
Shortest path distance for graph 3: -19

Shortest shortest path distance: -19

TIME IN loading graphs:           0.40s
TIME IN finding shortest paths:  10.83s
```

**Note:** The files `g1.txt`, `g2.txt` and `g3.txt` have been provided here,
and have been used for the program to run.
