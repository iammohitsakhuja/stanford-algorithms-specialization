#include "DualHeap.hh"

DualHeap::~DualHeap(void)
{
    // Empty the Max Heap.
    while (!this->max_heap.empty())
        this->max_heap.pop();

    // Empty the Min Heap.
    while (!this->min_heap.empty())
        this->min_heap.pop();
}

void DualHeap::push(int data)
{
    // Always push the first element to the Max Heap.
    if (this->max_heap.empty()) {
        this->max_heap.push(data);
        return;
    }

    // Push the element to the appropriate heap.
    if (data <= this->max_heap.top())
        this->max_heap.push(data);
    else
        this->min_heap.push(data);

    // If any of the two heaps gets too big, then pop its topmost element and
    // insert it into the other heap.
    if (this->max_heap.size() >= this->min_heap.size() + 2) {
        this->min_heap.push(this->max_heap.top());
        this->max_heap.pop();
    } else if (this->min_heap.size() >= this->max_heap.size() + 2) {
        this->max_heap.push(this->min_heap.top());
        this->min_heap.pop();
    }
}

int DualHeap::median(void)
{
    // More elements in Min Heap means that, it has the median.
    if (this->min_heap.size() > this->max_heap.size())
        return this->min_heap.top();

    // In all other cases, Max Heap has the median.
    return this->max_heap.top();
}
