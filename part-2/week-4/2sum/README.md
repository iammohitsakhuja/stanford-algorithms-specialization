# 2-Sum

## Overview

This folder contains a program that implements the 2-Sum algorithm wherein
a large number of 64-bit integers and a range of target values is provided,
and the goal is to compute the number of target values that can be achieved by
adding two distinct numbers from the given input.

The file provided here `algo-programming_prob-2sum.txt` contains 1,000,000
numbers. (Need to unzip the zip file first). And the target value range used
is: [-10000, 10000], hence a total of 20001 numbers.

### Why multiple languages

As it is evident, the same program has been implemented using 3 different
languages:

- Python
- JavaScript
- C

The reason is to illustrate the performance of each language. Python and JS
implementations use the in-built hash-table (set) whereas C implementation uses
a self-written hash-table with the Hash function coming from
[Thomas Mueller's answer](https://stackoverflow.com/a/12996028/8158281) at
StackOverflow.

## Usage and output

**CAUTION:** All the implementations take a huge amount of time to run on a
decent notebook (even though C is faster by a ton, obviously), given that the
size of the input is of the same order as used here.

### Python

#### Requirements for running Python program

- Must have Python3 installed.

#### Argument structure for Python program

- `2sum.py` - Name of the Python file.
- `algo1-programming_prob-2sum.txt` - File containing 1000000 64-bit integers.
- `-10000` - Lower limit of the target range.
- `10000` - Upper limit of the target range.

```bash
$ unzip algo1-programming_prob-2sum.zip
$ python 2sum.py algo1-programming_prob-2sum.txt -10000 10000
No. of distinct numbers: 999752
Count of achievable targets: 427

TIME IN loading the numbers into the hash table:    0.597s
TIME IN counting achievable targets:             3845.675s
TIME IN total:                                   3846.272s
```

### JavaScript

#### Requirements for running JavaScript program

- Must have Node (>=8.11.4) installed.

**NOTE:** Argument structure is the same as that of Python program, except that
now the file to be run is `2sum.js`.

```bash
$ unzip algo1-programming_prob-2sum.zip
$ node 2sum.js algo1-programming_prob-2sum.txt -10000 10000
No. of distinct numbers: 999752
Count of achievable targets: 427

TIME IN loading the numbers into the hash table:       0.611s
TIME IN counting achievable targets:                4316.412s
TIME IN total:                                      4317.023s
```

### C

#### Requirements for running C program

- Must have a C11 compiler.
- (Optional) `make` utility.

#### Argument structure for C program

- `2sum` - Name of the executable.
- `algo1-programming_prob-2sum.txt` - File containing 1000000 64-bit integers.
- `1000000` - Need to explicitly provide the total no. of numbers being given.
- `-10000` - Lower limit of the target range.
- `10000` - Upper limit of the target range.

```bash
$ make
$ rm *.o
$ ./2sum algo1-programming_prob-2sum.txt 1000000 -10000 10000
Number of collisions:        213548
Count of achievable targets:    427

TIME IN loading:      0.14s
TIME IN unloading:    0.17s
TIME IN counting:  1364.37s
TIME IN total:     1364.68s
```
