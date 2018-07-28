# Closest Pair Algorithm

## Overview

This directory contains the program that implements O(nlogn) version of
Closest Pair Algorithm.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make ../rand
$ make
$ ../rand 10000000 1000000000 | ./closest_pair 20000
Closest pair according to brute force:
Pair: ((861679153, 759292750), (861631970, 759266647))

Closest pair according to O(nlogn) algorithm:
Pair: ((861631970, 759266647), (861679153, 759292750))

TIME IN calculating result by brute force:             17.45
TIME IN calculating result by closest pair algorithm:  0.06
TIME IN TOTAL:                                         17.51

All tests passed!
```

**Note:** The order of the points inside the two pairs that have been
calculated using the two approaches might be different (as is the case in the
example shown above). While testing for correction, this has been taken
care of.

**Disclaimer:** The time to find the closest pair amongst 20000 points may
vary depending on your machine.

