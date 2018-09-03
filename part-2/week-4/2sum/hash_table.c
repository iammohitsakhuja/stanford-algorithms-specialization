#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

extern int collisions;

static Node *create_new_node(int64_t data)
{
    // Allocate memory for a new node.
    Node *new_node = (Node *)malloc(sizeof(Node));

    // Only if the new node now exists, update it.
    if (new_node) {
        new_node->data = data;
        new_node->next = NULL;
    }

    // Leave checking for NULL to be handled in the calling method.
    return new_node;
}

Node **load(const int64_t *array, size_t SIZE)
{
    // Allocate memory for a hash table.
    Node **hash_table = (Node **)malloc(HASH_SIZE * sizeof(Node *));

    // Safety check.
    if (!hash_table) {
        fprintf(stderr, "Error creating a hash table\n");
        return NULL;
    }

    // Insert the array values into the hashtable.
    for (size_t i = 0; i < SIZE; i++) {
        // Create a new node with the current array value.
        Node *new_node = create_new_node(array[i]);

        // Safety check.
        if (!new_node) {
            fprintf(stderr, "Error creating a new node\n");
            unload(hash_table);
            return NULL;
        }

        // Calculate the position at which the new node will be inserted.
        uint64_t index = hash(array[i]) % HASH_SIZE;

        // Keep track of the number of collisions.
        if (hash_table[index])
            collisions++;

        // Insert the new node at the beginning of the linked list at the
        // `index` position.
        new_node->next    = hash_table[index];
        hash_table[index] = new_node;
    }

    return hash_table;
}

bool check(const Node **hash_table, int64_t data)
{
    // Safety check.
    if (!hash_table)
        return false;

    // Find the index where this data would be present at, if it exists.
    uint64_t index = hash(data) % HASH_SIZE;

    // Start checking from the beginning of the indexed linked list.
    Node *curr_node = (Node *)hash_table[index];

    while (curr_node) {
        // Compare the `data` value at the current node with the given `data`
        // value.
        if (curr_node->data == data)
            return true;

        // Proceed to check the next node in the linked list.
        curr_node = curr_node->next;
    }

    return false;
}

bool unload(Node **hash_table)
{
    for (size_t i = 0; i < HASH_SIZE; i++) {
        // Get the first node of the linked list, if it exists.
        Node *curr_node = hash_table[i];

        // While `curr_node` doesn't fall off the end of the list.
        while (curr_node) {
            // Get the next node in the list (might be NULL).
            Node *next_node = curr_node->next;

            // Free the current node.
            free(curr_node);

            // Go to the next node.
            curr_node = next_node;
        }
    }

    return true;
}

/**
 * Taken from Thomas Mueller's answer at StackOverflow, which is available
 * here at: https://stackoverflow.com/a/12996028/8158281
 *
 * Specifically used for hashing 64-bit integers.
 */
uint64_t hash(uint64_t x)
{
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}
