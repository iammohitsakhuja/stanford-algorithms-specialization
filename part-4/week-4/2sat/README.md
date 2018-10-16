# 2-SAT Problem

## Overview

This folder contains a program that solves the 2-SAT problem for the given
symbols and clauses by representing them using a directed graph, and computing
the SCCs (using Kosaraju's algorithm).

### Execution steps

To run and test it out for yourself, follow these steps:

```bash
$ unzip 2sat.zip
Archive:  2sat.zip
  inflating: 2sat1.txt
  inflating: 2sat2.txt
  inflating: 2sat3.txt
  inflating: 2sat4.txt
  inflating: 2sat5.txt
  inflating: 2sat6.txt
$ make
$ ./2sat 6 2sat1.txt 2sat2.txt 2sat3.txt 2sat4.txt 2sat5.txt 2sat6.txt
File 1: Satisfiable
File 2: Non-satisfiable
File 3: Satisfiable
File 4: Satisfiable
File 5: Non-satisfiable
File 6: Non-satisfiable

BENCHMARK RESULTS:
TIME IN loading graph 1:                       0.094s
TIME IN loading graph 2:                       0.186s
TIME IN loading graph 3:                       0.380s
TIME IN loading graph 4:                       0.520s
TIME IN loading graph 5:                       0.711s
TIME IN loading graph 6:                       0.965s

TIME IN computing SCCs for graph 1:            0.315s
TIME IN computing SCCs for graph 2:            0.656s
TIME IN computing SCCs for graph 3:            1.334s
TIME IN computing SCCs for graph 4:            1.901s
TIME IN computing SCCs for graph 5:            2.646s
TIME IN computing SCCs for graph 6:            3.451s

TIME IN computing satisfiability for graph 1:  0.001s
TIME IN computing satisfiability for graph 2:  0.002s
TIME IN computing satisfiability for graph 3:  0.004s
TIME IN computing satisfiability for graph 4:  0.007s
TIME IN computing satisfiability for graph 5:  0.008s
TIME IN computing satisfiability for graph 6:  0.010s

TOTAL TIME IN loading graphs:                  2.855s
TOTAL TIME IN computing sccs:                 10.304s
TOTAL TIME IN computing satisfiability:        0.032s

TOTAL TIME:                                   13.191s
```

**Note:** A zip file `2sat.zip` has been provided here, and contains the
following files:

- `2sat1.txt`
- `2sat2.txt`
- `2sat3.txt`
- `2sat4.txt`
- `2sat5.txt`
- `2sat6.txt`

These files have been used for the demonstration showed above.

**Disclaimer:** The time to find the satisfiability of a given set of inputs
may vary depending on your machine.
