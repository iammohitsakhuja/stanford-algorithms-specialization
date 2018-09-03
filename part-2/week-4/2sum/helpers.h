/**
 * Author: Mohit Sakhuja
 * Dated: 03/09/2018
 *
 * Contains helper/utility function declarations for the C-implementation of
 * the 2-Sum algorithm.
 */

#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "hash_table.h"

int64_t *load_from_file(const char *FILE_NAME, size_t SIZE);
int count_achievable_targets(const int64_t *array, size_t SIZE,
    const Node **hash_table, int64_t start, int64_t end);

#endif
