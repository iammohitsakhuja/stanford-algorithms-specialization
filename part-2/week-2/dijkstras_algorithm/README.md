# Dijkstra's algorithm

## Overview

This folder contains a program that implements Dijkstra's algorithm for
computing shortest distances between a source vertex and every other vertex in
a directed weighted graph.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ ./dijkstras_algorithm dijkstraData.txt 200 1 10 7 37 59 82 99 115 133 165 188 197
 src -> dest (dist)
   1 ->    7 (2599)
   1 ->   37 (2610)
   1 ->   59 (2947)
   1 ->   82 (2052)
   1 ->   99 (2367)
   1 ->  115 (2399)
   1 ->  133 (2029)
   1 ->  165 (2442)
   1 ->  188 (2505)
   1 ->  197 (3068)

TIME IN loading graph:          6.283ms
TIME IN calculating distances:  0.628ms
TIME IN total:                  6.911ms
```

### Program arguments

1. `dijkstraData.txt` - File containing the vertices and weighted edges.
1. `200` - Number of vertices in the graph. Need to specify it manually.
1. `1` - Source vertex number.
1. `10` - (Optional) Number of vertices for which to show output.
1. `7 37 ... 188 197` - (Optional but required when 4th argument is provided)
    Vertices for which to show output.

**Note:** The file `dijkstraData.txt` has been provided here, and is used for
the program to run.

