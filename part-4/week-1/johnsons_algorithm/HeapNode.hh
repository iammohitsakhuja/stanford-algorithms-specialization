/**
 * Author: Mohit Sakhuja
 * Dated: 27/08/2018
 *
 * Represents a node in the heap.
 */

#ifndef HEAPNODE_HH
#define HEAPNODE_HH

struct HeapNode {
    // The vertex this node represents.
    int vertex;

    // Minimum distance of this vertex from that part of the graph which is not
    // included in the heap.
    int distance;

    HeapNode(int __vertex, int __distance);
};

#endif