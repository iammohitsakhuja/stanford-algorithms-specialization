/**
 * Author: Mohit Sakhuja
 * Dated: 02/09/2018
 *
 * Represents a data structure consisting of 2 heaps - a min heap and a max
 * heap.
 */

#ifndef DUAL_HEAP_HH
#define DUAL_HEAP_HH

#include <queue>

using namespace std;

class DualHeap {
private:
    // Provides the maximum of the smallest half elements.
    priority_queue<int> max_heap;

    // Provides the minimum of the largest half elements.
    priority_queue<int, vector<int>, greater<int>> min_heap;

public:
    // Memory management.
    ~DualHeap(void);

    // Add an element.
    void push(int data);

    // Returns the current median.
    int median(void);
};

#endif
