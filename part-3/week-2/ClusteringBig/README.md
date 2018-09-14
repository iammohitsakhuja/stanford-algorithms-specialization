# Clustering Big

## Overview

This folder contains a program that implements a program that finds the maximum
number of clusters such that there is a k-clustering with the spacing provided.

## Working

The program makes use of a Union-Find data structure that utilises
`Union by rank` and `Path compression` techniques to optimize its finding and
union capabilities. The running time for those operations becomes: `O(α(n))`
where `α` represents the `Inverse Ackermann function`.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java ClusteringBig clustering_big.txt 3
Max clusters: 6118

TIME IN loading labels:             938.83ms
TIME IN finding the max clusters:  5895.03ms
```

**Disclaimer:** The actual times depicted here may vary depending on your
machine.
