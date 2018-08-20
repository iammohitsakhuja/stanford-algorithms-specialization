#ifndef HELPERS_HPP
#define HELPERS_HPP

int choose_random_pivot(int *array, int first, int last);
int choose_pivot(
    int *array, int first, int last, int (*method)(int *, int, int));
int partition(int *array, int first, int last, int pivot);

#endif
