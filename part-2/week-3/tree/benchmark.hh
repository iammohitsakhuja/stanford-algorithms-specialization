/**
 * Author: Mohit Sakhuja
 * Dated: 26/08/2018
 *
 * Contains declarations for function to calculate time difference between
 * two timeval structures.
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

double calculate(const struct rusage *b, const struct rusage *a);

#endif
