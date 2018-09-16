# Max-Weight Independent Set

## Overview

This folder contains a program that finds the Max-Weight Independent Set of a
path graph with weighted vertices.

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac MaxWeightIndependentSet.java
$ java MaxWeightIndependentSet mwis.txt 8 1 2 3 4 17 117 517 997
Vertex:       Weight
     1:      4962786
     2:         null
     3:      5601590
     4:         null
    17:         null
   117:      7463231
   517:      5906419
   997:         null

Sum of weights in Max Weight Independent Set: 2955353732
```

### Program arguments

1. `mwis.txt` - File containing the weights of the vertices.
1. `8` - Number of vertices to show output for.
1. `1 2 .. 997` - Vertices for which to show output.

**Note:** The file `mwis.txt` has been provided here, and is used for the
program to run.
