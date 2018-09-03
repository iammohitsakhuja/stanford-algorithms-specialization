#include "benchmark.h"
#include <stdio.h>

// Returns number of seconds between b and a.
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
        return 0.0;

    return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec)
                 - (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec))
                + ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec)
                      - (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
        / 1000000.0);
}
