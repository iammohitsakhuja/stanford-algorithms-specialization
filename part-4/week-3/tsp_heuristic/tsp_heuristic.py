from sys import argv
from math import floor, sqrt
from time import time

from Point import Point


def load_points_from_file(file_name):
    """Loads points from a file into a list."""
    points = []

    # Open file for reading.
    with open(file_name) as file:
        # Get the number of points.
        num_points = int(file.readline())

        # Read the coordinates of each point, and add it to the list of all points.
        for i in range(num_points):
            coordinates = file.readline().split()
            x = float(coordinates[1])
            y = float(coordinates[2])
            points.append(Point(x, y))

    return points


def calculate_distance_between(a, b):
    """Returns the square of distance between two points."""
    return (a.x - b.x) ** 2 + (a.y - b.y) ** 2


def find_minimum_cost_tour_nn(points):
    """Find the minimum cost tour by using the Nearest Neighbors heuristic."""
    is_visited = [False for i in range(len(points))]

    # Start from the first point.
    total_cost = 0
    is_visited[0] = True
    total_visited = 1
    last_visited = 0

    while total_visited != len(points):
        min_dist = float("inf")
        min_dist_index = -1

        # Find the point with minimum distance from the last visited point.
        for i in range(len(points)):
            if is_visited[i] == False:
                distance = calculate_distance_between(
                    points[i], points[last_visited])
                if distance < min_dist:
                    min_dist = distance
                    min_index = i

        # Mark the point with minimum distance as visited, and add its distance to the total cost.
        is_visited[min_index] = True
        last_visited = min_index
        total_cost += sqrt(min_dist)
        total_visited += 1

    # Add the distance of the last visited point from the first point, to the total cost.
    total_cost += sqrt(calculate_distance_between(
        points[0], points[last_visited]))

    return total_cost


def main(argv):
    """Main function for the program."""

    # Ensure proper usage.
    if len(argv) != 2:
        print("Usage: python %s <file_name>" % argv[0])
        exit(1)

    # Get the inputs.
    file_name = argv[1]

    # Load points from file.
    load_start_time = time()
    points = load_points_from_file(file_name)
    load_end_time = time()
    time_loading_points_from_file = load_end_time - load_start_time

    # Calculate the minimum cost tour by using the Nearest Neighbors heuristic.
    tour_start_time = time()
    min_cost = find_minimum_cost_tour_nn(points)
    tour_end_time = time()
    time_finding_minimum_cost_tour_nn = tour_end_time - tour_start_time

    # Display the results.
    print("Approximate cost of minimum cost tour: " +
          str(floor(min_cost)), end="\n\n")

    # Display the benchmark results.
    print("TIME IN loading points from file:              %8.3fs" %
          time_loading_points_from_file)
    print("TIME IN finding minimum cost tour (heuristic): %8.3fs" %
          time_finding_minimum_cost_tour_nn)
    print("TIME IN total:                                 %8.3fs" %
          (time_loading_points_from_file + time_finding_minimum_cost_tour_nn))


if __name__ == '__main__':
    main(argv)
