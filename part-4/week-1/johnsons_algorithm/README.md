# Johnson's algorithm

## Overview

This folder contains a program that implements Johnson's algorithm for finding
All Pairs' Shortest Path Distances in a directed weighted graph.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./johnsons_algorithm 3 ../g1.txt ../g2.txt ../g3.txt
Graph  1: Cycle exists!
Graph  2: Cycle exists!
Shortest path distance for graph 3: -19

Shortest shortest path distance: -19

TIME IN loading graph 1:                            0.02s
TIME IN loading graph 2:                            0.02s
TIME IN loading graph 3:                            0.02s

TIME IN calculating shortest paths for graph 1:     0.94s
TIME IN calculating shortest paths for graph 2:     1.12s
TIME IN calculating shortest paths for graph 3:     2.66s

TOTAL TIME IN loading graphs:                       0.07s
TOTAL TIME in calculating shortest paths:           4.72s

TIME IN TOTAL:                                      4.79s
$ ./johnsons_algorithm 1 ../large.txt
Shortest path distance for graph 1: -6

Shortest shortest path distance: -6

TIME IN loading graph 1:                            0.46s

TIME IN calculating shortest paths for graph 1:  1277.84s

TOTAL TIME IN loading graphs:                       0.46s
TOTAL TIME in calculating shortest paths:        1277.84s

TIME IN TOTAL:                                   1278.29s
```

**Note:** The files `g1.txt`, `g2.txt`, `g3.txt` and `large.txt` have been
provided here, and are used for the program to run.

**Disclaimer:** The time to find the APSP may vary depending on your machine.
