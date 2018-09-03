/**
 * Author: Mohit Sakhuja
 * Dated: 03/09/2018
 *
 * Contains declarations for a Hash Table of integers, and the operations that
 * can be performed on it.
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HASH_SIZE 1999993

// Represents a single node in the hash table.
typedef struct node {
    int64_t data;
    struct node *next;
} Node;

// Operations.
bool check(const Node **hash_table, int64_t data);
Node **load(const int64_t *array, size_t SIZE);
bool unload(Node **hash_table);

// Hash function.
uint64_t hash(uint64_t data);

extern int collisions;

#endif
