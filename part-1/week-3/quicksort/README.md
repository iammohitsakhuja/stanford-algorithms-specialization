# Quick Sort

## Overview

This folder contains a program that implements the Quicksort algorithm.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./quicksort 10000000
Number of comparisons with first element as pivot: 289033668
Number of comparisons with last element as pivot:  288997053
Number of comparisons with median as pivot:        248659982
Number of comparisons with a random pivot:         283919606

TIME IN sorting (first element):    4.37
TIME IN sorting (last element):     4.35
TIME IN sorting (median):           4.09
TIME IN sorting (random):           4.43
TIME IN sorting (merge sort):       8.87
TIME IN TOTAL:                     26.11

All tests passed!
```

**Note:** The actual sorted array is not shown. Instead, the program file
includes a test that checks whether the array is sorted in ascending order or
not.

**Disclaimer:** The time to sort 10 million numbers that has been shown above
may vary depending on your machine.

