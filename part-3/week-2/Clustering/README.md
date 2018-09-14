# Max-Spacing K-Clustering

## Overview

This folder contains a program that finds the max-spacing for a k-clustering of
a given graph.

`Spacing` is defined as the minimum distance between two points `p` and `q`
that lie in different clusters. Hence, the max-spacing problem is to find such
a clustering of k-clusters that this spacing is maximized.

## Working

The program makes use of a Union-Find data structure that utilises
`Union by rank` and `Path compression` techniques to optimize its finding and
union capabilities. The running time for those operations becomes: `O(α(n))`
where `α` represents the `Inverse Ackermann function`.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java Clustering clustering1.txt 4
Maximum spacing: 106

TIME IN loading graph:           325.50ms
TIME IN finding the max spacing:  50.82ms
```

**Disclaimer:** The actual times depicted here may vary depending on your
machine.
