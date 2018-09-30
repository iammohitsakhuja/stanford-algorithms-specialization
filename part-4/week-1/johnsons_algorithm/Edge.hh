/**
 * Author: Mohit Sakhuja
 * Dated: 30/09/2018
 *
 * Represents an edge.
 */

#ifndef EDGE_HH
#define EDGE_HH

class Edge {
private:
    int dest;
    int weight;

public:
    Edge(int __dest, int __weight);

    int  get_dest(void);
    int  get_weight(void);
    void update_weight(int __weight);
};

#endif