/**
 * Author: Mohit Sakhuja
 * Dated: 16/10/2018
 *
 * Contains helper function declarations for the 2-SAT program.
 */

#ifndef HELPERS_HH
#define HELPERS_HH

#include <vector>

#include "Graph.hh"

using namespace std;

void   add_edges_to_graph(Graph &graph, int u, int v, int num);
Graph *load_graph_from_file(const char *file_name);
bool   get_satisfiability(vector<int> strongly_connected_components, int n);
bool   compute_satisfiability(const char *file_name,
      double &time_loading_graph_from_file, double &time_computing_scc,
      double &time_computing_satisfiability);

#endif
