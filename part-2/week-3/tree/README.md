# Binary Search Trees

## Overview

This folder contains a program that implements the Binary Search Tree data
structure with the following operations:

- Push (Inserts an element into the tree)
- Pop (Removes the element with the given key from the tree)
- Traverse (Performs the In-Order traversal of the tree)
- Search (Tells whether an element with a given key is present in the tree or
    not)
- Min (Returns the element with the smallest key in the tree)
- Max (Returns the element with the largest key in the tree)
- Select (Returns the ith order element, provided that ith order element
    exists)
- Predecessor (Returns the largest element after which the key may lie in the
    tree)
- Successor (Returns the smallest element before which the key may lie in the
    tree)
- Rank (Returns the number of keys less than or equal to the given key)
- Size (returns the number of elements in the tree)
- Empty (Tells whether the tree has any elements[`false`] or not[`true`])

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./tree 10000000
Insertion tests passed!
Actual array sorted!
In-order traversal tests passed!
Searching tests passed!
Selection tests passed!
Min/max tests passed!
Predecessor tests passed!
Successor tests passed!
Rank tests passed!
Deletion tests passed!
Clearing tests passed!

All tests passed!

TIME IN insertion and its testing:            12.76s
TIME IN sorting the array:                     0.75s
TIME IN traversal and its testing:             3.61s
TIME IN searching and its testing:             2.20s
TIME IN selection and its testing:             2.66s
TIME IN min/max and its testing:               0.00s
TIME IN finding predecessors and its testing: 15.92s
TIME IN finding successors and its testing:   15.34s
TIME IN ranking and its testing:               5.55s
TIME IN deletion and its testing:              0.05s
TIME IN clearing the tree and its testing:     4.09s
TIME IN total (excluding sorting the array):  56.62s
```

**Note:** The actual tree is not shown. Instead, the program contains various
tests to test whether each operation has been performed correctly or not.

**Disclaimer:** The time to perform various operations on 10 million numbers
that is shown here may vary depending on your machine.

