# Bellman-Ford Algorithm

## Overview

This folder contains a program that implements the Bellman-Ford algorithm to
find the shortest paths to every other reachable vertex from a source vertex in
a directed weighted graph (negative edge lengths allowed).

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java -ea BellmanFord
Test without negative cost cycle passed successfully!
Test with negative cost cycle(s) passed successfully!
All tests passed!
```

**Note:** The actual output of the algorithm (i.e. the paths) are not
shown. Instead, the program contains tests for two graphs - one with a negative
cost cycle, and one without. These test cases have been taken from
GeeksForGeeks - see [here](https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)
and [here](https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/).
