# Sequence Alignment

## Overview

Sequence Alignment problem is about aligning two strings in a way that it
minimizes the total penalty (which is given) of creating gaps and/or matching
two characters.

This folder contains a program that implements the Sequence Alignment problem.

### Execution Steps

To run and test it out for yourself, follow these steps:

```bash
$ javac *.java
$ java -ea SequenceAlignmentTest
All tests passed!
```

**Disclaimer:** The actual output of the strings to be aligned is not shown.
Instead, the program contains tests for a few set of strings that are shown
below. Test cases 2-4 have been taken from [GeeksForGeeks](https://www.geeksforgeeks.org/sequence-alignment-problem/).

## Test Cases

### Test Case 1

#### Inputs 1

- String1: `AACAGTTACC`
- String2: `TAAGGTCA`
- Gap penalty: 2
- Mismatch penalty: 1

#### Outputs 1

- Expected result string1: `AACAGTTACC`
- Expected result string2: `TA-AGGT-CA`
- Expected penalty: 7

### Test Case 2

#### Inputs 2

- String1: `CG`
- String2: `CA`
- Gap penalty: 3
- Mismatch penalty: 7

#### Outputs 2

- Expected result string1: `CG-`
- Expected result string2: `C-A`
- Expected penalty: 6

### Test Case 3

#### Inputs 3

- String1: `CG`
- String2: `CA`
- Gap penalty: 3
- Mismatch penalty: 5

#### Outputs 3

- Expected result string1: `CG`
- Expected result string2: `CA`
- Expected penalty: 5

### Test Case 4

#### Inputs 4

- String1: `AGGGCT`
- String2: `AGGCA`
- Gap penalty: 3
- Mismatch penalty: 2

#### Outputs 4

- Expected result string1: `AGGGCT`
- Expected result string2: `A-GGCA`
- Expected penalty: 5
