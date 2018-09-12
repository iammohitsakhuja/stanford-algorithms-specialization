# Prim's Minimum Spanning Tree Algorithm

## Overview

This folder contains a program that implements Prim's algorithm for finding the
Minimum Spanning Tree of an undirected weighted graph, with positive and
negative edge lengths.

## Working

The program makes use of a custom Heap that, along with supporting the usual
operations like `push`, `pop`, `top`, `bubbleUp`, `bubbleDown` etc, also
supports the `deleteKey` operation. This makes it possible to delete an element
from the heap in Logarithmic time. This functionality has been achieved by
keeping a mapping of keys with the indices. In this implementation, it only
works with integers.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java PrimsMSTAlgorithm edges.txt
Overall cost: -3612829

TIME IN loading graph:    74.79ms
TIME IN finding the MST:   9.95ms
```

**Disclaimer:** The actual times depicted here may vary depending on your
machine.
