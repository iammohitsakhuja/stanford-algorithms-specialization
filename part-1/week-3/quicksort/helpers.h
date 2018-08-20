#ifndef HELPERS_H
#define HELPERS_H

void swap(int *a, int *b);
int choose_first_element_as_pivot(int *array, int first, int unused);
int choose_last_element_as_pivot(int *array, int first, int last);
int choose_median_as_pivot(int *array, int first, int last);
int choose_random_pivot(int *array, int first, int last);
int choose_pivot(
    int *array, int first, int last, int (*method)(int *, int, int));
int partition(int *array, int first, int last, int pivot);

#endif
