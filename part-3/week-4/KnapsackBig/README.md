# Knapsack Big Problem

## Overview

This folder contains a program that solves the Knapsack problem in which a
**LARGE** no. of items are provided, each with its own value and weight. The
size of the knapsack is also provided. For the problem definition, items are to
be chosen in such a way that the sum of their values needs to be maximized
while making sure that their collective weights do not go beyond the size of
the knapsack.

The size of the knapsack instance is so big that the straightforward iterative
implemetation uses an infeasible amount of time and space.

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac KnapsackBig.java
$ java KnapsackBig knapsack_big.txt
Best value: 4243395

TIME IN loading the knapsack items from the file: 0.063s
TIME IN calculating best value:                   2.006s
TIME IN total:                                    2.068s
```

**Note:** The file `knapsack_big.txt` has been provided here, and is used for
the program to run.
