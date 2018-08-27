#include <fstream>
#include <sstream>

#include "helpers.hh"

void load_graph_from_file(Graph &G, int n, char *file_name)
{
    // Open the file.
    ifstream file;
    file.open(file_name);

    // Check for file's existence and related permissions.
    if (file.fail()) {
        fprintf(stderr,
            "Error: Either %s does not exist or you do not have enough "
            "permissions to open it\n",
            file_name);
        exit(1);
    }

    // Read from the file.
    for (int i = 0; i < n && file; i++) {
        // Read a single line and convert it into a stream.
        string line;
        getline(file, line);
        istringstream linestream(line);

        // First entry in the line is the tail vertex.
        // Read the tail vertex and store it.
        string tail;
        getline(linestream, tail, '\t');

        // Read the rest of the line.
        while (linestream) {
            // Extract each edge from the line.
            string edge;
            linestream >> edge;

            if (edge.length() != 0) {
                // Convert the edge to a stream, and read head & weight data.
                istringstream edgestream(edge);
                string head;
                string weight;

                getline(edgestream, head, ',');
                getline(edgestream, weight);

                // Add edge from 'tail' to 'head' with a 'weight'.
                G.add_edge(stoi(tail), stoi(head), stoi(weight), true);
            }
        }
    }

    // Housekeeping.
    file.close();
}
