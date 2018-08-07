from random import choice
from copy import deepcopy
from time import time
import sys


def load_graph(graph, file_name):
    """Loads a graph."""
    # Open the file.
    with open(file_name) as g_file:
        # Each line contains a vertex and all other vertices it is connected
        # to.
        for line in g_file.readlines():
            vertices = line.split()
            graph[vertices[0]] = vertices[1:]


def get_random_edge(graph):
    """Chooses an edge randomly."""
    # Choose a vertex randomly.
    v1 = choice(list(graph.keys()))

    # Choose another vertex from the list of vertices that v1 is connected to.
    v2 = choice(list(graph[v1]))

    # Return the pair of vertices corresponding an edge.
    return (v1, v2)


def karger_algorithm(graph):
    while len(graph) > 2:
        (v1, v2) = get_random_edge(graph)
        graph[v1].extend(graph[v2])

        # Change each occurrence of v2 in the graph to v1.
        for vertex in graph[v2]:
            graph[vertex].remove(v2)
            graph[vertex].append(v1)

        # Remove self-loops.
        while v1 in graph[v1]:
            graph[v1].remove(v1)

        # Contract the vertex v2 into v1.
        del graph[v2]

    length = [len(graph[key]) for key in graph.keys()]
    return length[0]


def main(argv):
    """Main function for the program."""
    if len(argv) != 2:
        print("Usage: python %s filename" % argv[0])
        return

    file_name = argv[1]

    # Empty graph as a dictionary.
    graph = {}

    # Load the points into the graph.
    # Each vertex is a represented by a key, whose value is another dictionary
    # of vertices that the vertex is connected to.
    load_graph(graph, file_name)

    # Find the minimum cut, and benchmark the time taken.
    initial_time = time()
    min_cut = karger_algorithm(deepcopy(graph))
    for i in range(len(graph.keys())):
        cut = karger_algorithm(deepcopy(graph))
        min_cut = cut < min_cut and cut or min_cut

    final_time = time()

    print("Minimum cut count:", min_cut)
    print("TIME TAKEN to find the minimum cut: %.5ss" %
          (final_time - initial_time))


main(sys.argv)
