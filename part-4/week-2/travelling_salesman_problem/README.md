# Travelling Salesman Problem

## Overview

This folder contains a program that finds the minimum cost tour for a
travelling salesman i.e. given n vertices, it finds a minimum cost tour (a
cyclic path) that visits all vertices.

### Execution steps

To run it for yourself, follow these steps:

```bash
$ make
$ ./tsp tsp.txt
Cost of minimum cost tour: 26442

TIME IN loading points from file:    0.20ms
TIME IN creating distance matrix:    0.08ms
TIME IN finding minimum cost tour:   92.60s
TIME IN total:                       92.60s
```

**Warning:** This program takes an **ABSURD** amount of RAM to run (about 4.5 GB
for 25 vertices given in the file provided), which is given since it uses an
exponential amount of memory: `n * (2^n)`. Make sure you have enough available
RAM before trying to run the program. Also, you can change the number `25` in the
file provided to something low - in order to still execute the program but by using
less memory.

**Disclaimer:** The time required to find a minimum cost tour for 25 vertices
that has been shown above - may vary depending on your machine.
