/**
 * Author: Mohit Sakhuja
 * Dated: 28/08/2018
 *
 * Represents the Heap Data Structure.
 */

#ifndef HEAP_HH
#define HEAP_HH

#include <vector>

using namespace std;

class Heap {
private:
    vector<int> array;

    // Helper functions.
    static int get_left_child_index(int index);
    static int get_right_child_index(int index);
    static int get_parent_index(int index);

    bool has_left_child(int index);
    bool has_right_child(int index);
    bool has_parent(int index);

    int left_child(int index);
    int right_child(int index);
    int parent(int index);

    void swap(int first_index, int second_index);

    void bubble_up(void);
    void bubble_down(int curr_index);

public:
    /* Heap operations */
    // Add an element to the heap.
    void push(int element);

    // Remove the topmost element from the heap.
    void pop(void);

    // Batch insert into a heap.
    void heapify(vector<int> array);

    // Return the topmost element from the heap.
    int top(void);

    // Returns true if the heap is empty.
    bool empty(void);

    // Returns the number of elements in the heap.
    int size(void);
};

#endif
