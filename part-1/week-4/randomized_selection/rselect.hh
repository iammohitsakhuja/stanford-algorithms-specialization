#ifndef RSELECT_HPP
#define RSELECT_HPP

int rselect(int *array, int first, int last, int order,
    int (*method)(int *, int, int));

#endif
