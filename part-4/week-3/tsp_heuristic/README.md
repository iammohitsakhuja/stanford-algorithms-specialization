# Travelling Salesman Problem by using Nearest Neighbor Heuristic

## Overview

This folder contains a program that finds the minimum cost tour (approx.) for a
travelling salesman i.e. given n vertices, it finds a minimum cost tour (a
cyclic path) that visits all vertices by using the `Nearest Neighbor` heuristic.
Since a heuristic is used, the answer is not the absolute optimal but in close
range to it. Also, the running time of this heuristic is O(n^2) instead of the
O(n^2 * 2^n) achieved by the proper soltuion.

### Execution steps

To run it for yourself, follow these steps:

```bash
$ python tsp_heuristic.py nn.txt
Approximate cost of minimum cost tour: 1203406

TIME IN loading points from file:                 0.051s
TIME IN finding minimum cost tour (heuristic):  371.920s
TIME IN total:                                  371.971s
```

**Disclaimer:** The time required to find the approximte cost of a minimum cost
tour for 33708 vertices that has been shown above - may vary depending on your
machine.
