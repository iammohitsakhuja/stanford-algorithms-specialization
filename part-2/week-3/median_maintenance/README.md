# Median Maintenance

## Overview

This folder contains a program that implements the Median Maintenance program.
It takes a list of integers (which are provided here in an unsorted manner)
that is treated as a stream of numbers, arriving one by one. At each arrival,
the current median is calculated and added to the total sum. Median is defined
as - if _k_ is the no. of integers that have arrived then, if _k_ is odd, then
median is _(k + 1)/2th_ element, and if _k_ is even, then median is _k/2th_
element.

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ make
$ cat Median.txt | ./median 10000
Median through heap = 46831213
Median through tree = 46831213

TIME IN calculating median via heap: 2.491ms
TIME IN calculating median via tree: 3.125ms

All tests passed!
```

**Disclaimer:** The time to maintain the median for 10000 numbers that is shown
here may vary depending on your machine.

