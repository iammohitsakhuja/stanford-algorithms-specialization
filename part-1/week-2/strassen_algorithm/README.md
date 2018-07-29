# Strassen's Algorithm for Matrix Multiplication

## Overview

This directory contains the program that implements Strassen's algorithm for
Matrix Multiplication. Usually, Matrix Multiplication is a O(n^3) task. But
Strassen's algorithm makes it possible to do the same in a O(n^2.80) bound.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./strassen_algorithm 1024
TIME IN calculating result by proper method:         17.22
TIME IN calculating result by Strassen's algorithm:  2.78
TIME IN TOTAL:                                       20.00

All tests passed!
```

**Warning:** The running time of this program rises sharply with the number of
points! Changing the number of points to 2000 or above might take more than
just a few minutes, but that is mainly due to the calculation by the proper
method.

**Disclaimer:** The time to multiply two 1024 x 1024 matrices may vary
depending on your machine.

