# Randomized Selection

## Overview

This folder contains a program that implements the Randomized Selection
algorithm for finding the kth order element in an array.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./randomized_selection 10000000 3848290
TIME IN finding the element (randomized selection): 0.21
TIME IN finding the element (quicksort):            2.03

All tests passed!
```

**Note:** The actual kth order element is not shown. Instead, the program file
includes a test that checks whether the kth order element found through
randomized selection algorithm is equal to the kth order element found by
first sorting the array via quicksort.

**Disclaimer:** The time to sort/find an element amongst 10 million numbers
that has been shown above may vary depending on your machine.

