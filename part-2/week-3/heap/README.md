# Heaps

## Overview

This folder contains a program that implements the Min-Heap data structure with
the following operations:

- Push (Pushes an element to the heap)
- Pop (Removes the top-most element from the heap)
- Heapify (Given an array, it inserts its values to the heap in O(n) time)
- Top (Returns the top-most element without removing it from the heap)
- Empty (Returns true/false depending on whether the heap is empty or not)
- Size (Returns the number of elements in the heap)

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./heap 10000000
TIME IN loading the heap via single insertions:   1.00s
TIME IN loading the heap via batch insertions:    0.68s
TIME IN popping after single insertions:         13.63s
TIME IN popping after batch insertions:          13.54s
TOTAL TIME IN single insertions method:          14.63s
TOTAL TIME IN batch insertions method:           14.23s
TIME IN total:                                   28.86s

All tests passed!
```

**Note:** The actual sorted array is not shown. Instead, the program file
includes a test that checks whether the array is sorted in ascending order
(since the heap implemented here is a Min-Heap) or not.

**Disclaimer:** The time to sort 10 million numbers that has been shown above
may vary depending on your machine.

