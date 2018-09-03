#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <sys/resource.h>

double calculate(const struct rusage *b, const struct rusage *a);

#endif
